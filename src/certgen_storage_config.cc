/*  =========================================================================
    certgen_storage_config - class description

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
    certgen_storage_config -
@discuss
@end
*/

#include "certgen_storage_config.h"

//  Structure of our class
namespace certgen
{
// StorageConfig
    void StorageConfig::load(const cxxtools::SerializationInfo& si)
    {
        si.getMember("storage_type") >>= m_storageType;
        si.getMember("permanent") >>= m_permanent;

        m_params = StorageConfigParams::create(m_storageType);
        
        si.getMember("storage_params") >>= *(m_params);
    }

    void operator>>= (const cxxtools::SerializationInfo& si, StorageConfig & config)
    {
        config.load(si);
    }

// StorageConfigParams
    StorageConfigParamsPtr StorageConfigParams::create(const std::string & storageType)
    {
        if(storageType == "secw")
        {
            return StorageConfigParamsPtr(new StorageConfigSecwParams());
        }
        else
        {
            throw std::runtime_error( "Storage type <"+storageType+"> is not supported");
        }
    }

    void operator>>= (const cxxtools::SerializationInfo& si, StorageConfigParams & configParams)
    {
        configParams.load(si);
    }

    void StorageConfigSecwParams::load(const cxxtools::SerializationInfo& si)
    {
        si.getMember("secw_portfolio") >>= m_portfolio;
        si.getMember("secw_document_name") >>= m_documentName;
        si.getMember("secw_document_usages") >>= m_documentUsages;
    }

} // namescpace certgen

//  --------------------------------------------------------------------------
//  Self test of this class
#define SELFTEST_DIR_RO "src/selftest-ro"
#define SELFTEST_DIR_RW "src/selftest-rw"

void
certgen_storage_config_test (bool verbose)
{
    printf (" * certgen_storage_config: ");

    //  @selftest
    //  Simple create/destroy test
    //  @end
    printf ("OK\n");
}

//  --------------------------------------------------------------------------
//  Self test of this class

// If your selftest reads SCMed fixture data, please keep it in
// src/selftest-ro; if your test creates filesystem objects, please
// do so under src/selftest-rw.
// The following pattern is suggested for C selftest code:
//    char *filename = NULL;
//    filename = zsys_sprintf ("%s/%s", SELFTEST_DIR_RO, "mytemplate.file");
//    assert (filename);
//    ... use the "filename" for I/O ...
//    zstr_free (&filename);
// This way the same "filename" variable can be reused for many subtests.
#define SELFTEST_DIR_RO "src/selftest-ro"
#define SELFTEST_DIR_RW "src/selftest-rw"

void
certgen_storage_config_test (bool verbose)
{
    printf (" * certgen_certificate_config: ");

    //  @selftest
    //  Simple create/destroy test
    //  @end
    printf ("OK\n");
}
