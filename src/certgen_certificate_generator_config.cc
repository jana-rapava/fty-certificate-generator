/*  =========================================================================
    certgen_certificate_generator_config - class description

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
    certgen_certificate_generator_config -
@discuss
@end
*/

#include "fty_certificate_generator_classes.h"

//  Structure of our class
namespace certgen
{

    CertificateConfig::CertificateConfig (const cxxtools::SerializationInfo & si)
    {
        si >>= *this;
    }

    void CertificateConfig::deserialize (const cxxtools::SerializationInfo & si)
    {
        si.getMember("signature_type") >>= m_signatureType;

        if (!si.findMember ("validity"))
        {
            throw std::runtime_error("empty value for validity");
        }
        si.getMember("validity") >>= m_validity;

        if (!si.findMember ("validity_offset"))
        {
            throw std::runtime_error("empty value for validity_offset");
        }
        si.getMember("validity_offset") >>= m_validityOffset;

        si.getMember("certificate_level") >>= m_certificateLevel;
    }

    void CertificateConfig::serialize (cxxtools::SerializationInfo & si) const
    {
        si.addMember("signature_type") <<= m_signatureType;

        si.addMember("validity") <<= m_validity;

        si.addMember("validity_offset") <<= m_validityOffset;

        si.addMember("certificate_level") <<= m_certificateLevel;
    }
} // namescpace certgen

void operator>>= (const cxxtools::SerializationInfo & si, certgen::CertificateConfig & config)
{
    config.deserialize (si);
}

void operator<<= (cxxtools::SerializationInfo & si, const certgen::CertificateConfig & config)
{
    config.serialize (si);
}

void
certgen_certificate_generator_config_test (bool verbose);
