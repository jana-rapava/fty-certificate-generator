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

//  Structure of our class

namespace certgen
{
    using namespace fty;
    using namespace std::placeholders;

    CertificateGeneratorServer::CertificateGeneratorServer()
    {
        //initiate the commands handlers
        m_supportedCommands[GENERATE_SELFSIGNED_CERTIFICATE] = std::bind(&CertificateGeneratorServer::handleGenerateSelfsignedCertificate, this, _1, _2);
        m_supportedCommands[GENERATE_CSR] = std::bind(&CertificateGeneratorServer::handleGenerateCSR, this, _1, _2);
        m_supportedCommands[IMPORT_CERTIFICATE] = std::bind(&CertificateGeneratorServer::handleImportCertificate, this, _1, _2);
    }

    Payload CertificateGeneratorServer::handleRequest(const Sender & sender, const Payload & payload)
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

            std::string result = cmdHandler(sender, params);
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

    std::string CertificateGeneratorServer::handleGenerateSelfsignedCertificate(const fty::Sender & /*sender*/, const fty::Payload & /*params*/)
    {
        std::string empty;
        return empty;
    }

    std::string CertificateGeneratorServer::handleGenerateCSR(const fty::Sender & /*sender*/, const fty::Payload & /*params*/)
    {
        std::string empty;
        return empty;
    }

    std::string CertificateGeneratorServer::handleImportCertificate(const fty::Sender & /*sender*/, const fty::Payload & /*params*/)
    {
        std::string empty;
        return empty;
    }

} // namescpace certgen

