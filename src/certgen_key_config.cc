/*  =========================================================================
    certgen_key_config - class description

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
    certgen_key_config -
@discuss
@end
*/

#include "certgen_key_config.h"

//  Structure of our class
namespace certgen
{
    // Static functions map
    std::map<std::string, std::function< KeyConfigParamsPtr() >> factoryFunctions =
    {
        { "RSA", []() { return KeyConfigParamsPtr(new KeyConfigRsaParams()); }},
        { "EC",  []() { return KeyConfigParamsPtr(new KeyConfigECParams()); }}
    };

    // KeyConfig
    void KeyConfig::load(const cxxtools::SerializationInfo& si)
    {
        si.getMember("key_type") >>= m_keyType;

        m_params = KeyConfigParams::create(m_keyType);
        
        si.getMember("key_params") >>= *(m_params);
    }

    void operator>>= (const cxxtools::SerializationInfo& si, KeyConfig & config)
    {
        config.load(si);
    }

// StorageConfigParams
    KeyConfigParamsPtr KeyConfigParams::create(const std::string & keyType)
    {
        return (factoryFunctions.at(keyType))();
    }

    void operator>>= (const cxxtools::SerializationInfo& si, KeyConfigParams & configParams)
    {
        configParams.load(si);
    }

    void KeyConfigRsaParams::load(const cxxtools::SerializationInfo& si)
    {
        si.getMember("rsa_length") >>= m_rsaLength;
    }

    void KeyConfigECParams::load(const cxxtools::SerializationInfo& si)
    {
        si.getMember("ec_curve_type") >>= m_ecCurveType;
    }

} // namescpace certgen


//  --------------------------------------------------------------------------
//  Self test of this class
#define SELFTEST_DIR_RO "src/selftest-ro"
#define SELFTEST_DIR_RW "src/selftest-rw"

void certgen_key_config_test (bool verbose)
{
    printf (" * certgen_key_config: ");

    //  @selftest
    //  Simple create/destroy test
    //  @end
    printf ("OK\n");
}
