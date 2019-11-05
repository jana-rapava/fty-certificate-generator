/*  =========================================================================
    certgen_certificate_generator_server - class description

    Copyright (C) 2014 - 2019 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

/*
@header
    certgen_certificate_generator_server -
@discuss
@end
*/

#include "fty_certificate_generator_classes.h"
#include <chrono>
#include <netdb.h>

// because there is NO std::chrono::days in C++14
#define HOURS_IN_DAY        24

#define COMMON_NAME         "Web server-ipm2-jana-selfsigned"
#define ORGANIZATION_UNIT   "Power quality"
#define ORGANIZATION        "Eaton"
#define LOCALITY            "Grenoble"
#define STATE               "38"
#define COUNTRY             "FR"
#define EMAIL               "noemail"

//  Structure of our class

namespace certgen
{
    using namespace fty;
    using namespace std::placeholders;

    CertificateGeneratorServer::CertificateGeneratorServer()
    {
        //initiate the commands handlers
        m_supportedCommands[GENERATE_SELFSIGNED_CERTIFICATE] = std::bind(&CertificateGeneratorServer::handleGenerateSelfsignedCertificate, this, _1);
        m_supportedCommands[GENERATE_CSR] = std::bind(&CertificateGeneratorServer::handleGenerateCSR, this, _1);
        m_supportedCommands[IMPORT_CERTIFICATE] = std::bind(&CertificateGeneratorServer::handleImportCertificate, this, _1);
    }

    Payload CertificateGeneratorServer::handleRequest(const Sender & /*sender*/, const Payload & payload)
    {
        try
        {
            if (payload.size() == 0)
            {
                throw std::runtime_error("Command frame is empty");
            }

            Command cmd = payload.at(0);
            if (cmd == "ERROR" || cmd == "OK")
            {
                //avoid loop
                return {};
            }

            //check if the command exists in the system
            if (m_supportedCommands.count(cmd) == 0)
            {
                throw std::runtime_error(cmd + "not supported");
            }
            FctCommandHandler cmdHandler = m_supportedCommands[cmd];

            //create copy of the payload
            std::vector<std::string> params(payload.begin() + 1, payload.end());

            std::string result = cmdHandler(params);
            return {result};
        }
        catch (std::exception &e)
        {
            log_error("Unexpected error: %s", e.what());
            return {"ERROR", e.what()};
        }
        catch (...) //show must go one => Log and ignore the unknown error
        {
            log_error("Unexpected error: unknown");
            return {"ERROR", ""};
        }
    }

    std::list<std::string> CertificateGeneratorServer::getSystemDomainNames()
    {
        char name[NI_MAXHOST];
        std::list<std::string> result;

        for (auto ipv4Address : getSystemIPs(AF_INET))
        {
            struct sockaddr sockAddr;
            memset (&sockAddr, 0, sizeof (sockAddr));

            sockAddr.sa_family = AF_INET;
            int rv = inet_pton (AF_INET, ipv4Address.c_str (), &sockAddr.sa_data);
            if (rv == 0)
            {
                throw std::runtime_error ("Invalid address");
            }

            if (rv == -1)
            {
                throw std::runtime_error ("Invalid address family");
            }

            rv = getnameinfo (&sockAddr, sizeof (sockAddr), name, sizeof (name), NULL, 0, NI_NAMEREQD);
            if (rv != 0)
            {
                log_error ("Error while getting hostname for IP address %s %s", ipv4Address.c_str(), gai_strerror (rv));
                continue;
            }

            auto it = std::find (result.begin(), result.end(), name);
            if (it == result.end())
            {
                result.push_back (name);
            }
        }

        for (auto ipv6Address : getSystemIPs(AF_INET6))
        {
            struct sockaddr sockAddr;
            memset (&sockAddr, 0, sizeof (sockAddr));

            sockAddr.sa_family = AF_INET6;
            int rv = inet_pton (AF_INET6, ipv6Address.c_str (), &sockAddr.sa_data);
            if (rv == 0)
            {
                throw std::runtime_error ("Invalid address");
            }

            if (rv == -1)
            {
                throw std::runtime_error ("Invalid address family");
            }

            rv = getnameinfo (&sockAddr, sizeof (sockAddr), name, sizeof (name), NULL, 0, NI_NAMEREQD);
            if (rv != 0)
            {
                log_error ("Error while getting hostname for IP address %s %s", ipv6Address.c_str(), gai_strerror (rv));
                continue;
            }

            auto it = std::find (result.begin(), result.end(), name);
            if (it == result.end())
            {
                result.push_back (name);
            }
        }

        return result;
    }

    std::list<std::string> CertificateGeneratorServer::getSystemIPs(int paramFamily)
    {
        struct ifaddrs *interfaces, *iface;
        char host[NI_MAXHOST];
        std::list<std::string> result;

        if (getifaddrs (&interfaces) == -1)
        {
            throw std::runtime_error ("Unable to get IP adresses");
        }
        iface = interfaces;
        for (iface = interfaces; iface != NULL; iface = iface->ifa_next)
        {
            if (iface->ifa_addr == NULL) continue;
            int family = iface->ifa_addr->sa_family;
            if (family == paramFamily)
            {
                if ( getnameinfo(iface->ifa_addr,
                        (family == AF_INET) ? sizeof(struct sockaddr_in) :
                        sizeof(struct sockaddr_in6),
                        host, NI_MAXHOST,
                        NULL, 0, NI_NUMERICHOST) == 0
                   )
                {
                    // sometimes IPv6 addres looks like ::2342%IfaceName
                    char *p = strchr (host, '%');
                    if (p) *p = 0;

                    auto it = std::find (result.begin(), result.end(), host);
                    if (it == result.end())
                    {
                        result.push_back (host);
                    }
                }
            }
        }
        freeifaddrs (interfaces);
        return result;
    }


    std::string CertificateGeneratorServer::handleGenerateSelfsignedCertificate(const fty::Payload & params)
    {
        // load config file for the service
        CertificateGeneratorConfig certgenConfig;

        if (params.empty() || params[0].empty ())
        {
            throw std::runtime_error ("Missing service name");
        }

        std::string serviceName (params[0]);
        std::string configFilePath(CONFIG_PATH + serviceName + ".cfg");
        std::ifstream configFile (configFilePath);
        if (!configFile)
        {
            throw std::runtime_error ("Could not open file " + configFilePath);
        }

        configFile.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
        std::stringstream configJson;
        configJson << configFile.rdbuf();
        configFile.close ();

        cxxtools::SerializationInfo certgenSi;
        cxxtools::JsonDeserializer deserializer (configJson);
        deserializer.deserialize (certgenSi);

        certgenSi >>= certgenConfig;

        fty::CertificateConfig config;
        // fill the configuration data
        uint8_t version;
        std::istringstream versionStr (certgenConfig.version());
        versionStr >> version;
        config.setVersion(version);

        std::chrono::hours validityOffset (HOURS_IN_DAY * certgenConfig.certConf().getValidityOffset());
        std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> currentTimestamp =
            std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
        std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> startTimestamp = currentTimestamp + validityOffset;
        config.setValidFrom(startTimestamp.time_since_epoch().count());

        std::chrono::hours validity (HOURS_IN_DAY * certgenConfig.certConf().getValidity());
        currentTimestamp = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
        std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> endTimestamp = currentTimestamp + validity;
        config.setValidTo(endTimestamp.time_since_epoch().count());

        config.setCountry(COUNTRY);
        config.setState(STATE);
        config.setLocality(LOCALITY);
        config.setOrganization(ORGANIZATION);
        config.setOrganizationUnit(ORGANIZATION_UNIT);
        config.setCommonName(COMMON_NAME);
        config.setEmail(EMAIL);

        std::list<std::string> ipList = getSystemIPs (AF_INET);
        ipList.merge (getSystemIPs (AF_INET6));
        config.setIpList(ipList);

        config.setDnsList(getSystemDomainNames());

        std::string keyType = certgenConfig.keyConf().keyType();
        std::string certPem;
        if (keyType == "RSA")
        {
            KeyConfigRsaParams *rsaParams = dynamic_cast<KeyConfigRsaParams *>(certgenConfig.keyConf().params().get());
            Keys keyPair = Keys::generateRSA(rsaParams->rsaLength());
            certPem = CertificateX509::selfSignSha256(keyPair, config).getPem();
        }
        else if (keyType == "EC")
        {
            KeyConfigECParams *ecParams = dynamic_cast<KeyConfigECParams *>(certgenConfig.keyConf().params().get());
            if (ecParams->ecCurveType() == "PRIME256v1")
            {
                Keys keyPair = Keys::generateEC (ECKeyType::PRIME256V1);
                certPem = CertificateX509::selfSignSha256(keyPair, config).getPem();
            }
        }
        else
        {
            throw std::runtime_error ("Invalid key type");
        }

        // TODO: store the certificate in security wallet
        return certPem;
    }

    std::string CertificateGeneratorServer::handleGenerateCSR(const fty::Payload & /*params*/)
    {
        std::string empty;
        return empty;
    }

    std::string CertificateGeneratorServer::handleImportCertificate(const fty::Payload & /*params*/)
    {
        std::string empty;
        return empty;
    }

} // namescpace certgen

