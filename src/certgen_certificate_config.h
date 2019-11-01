/*  =========================================================================
    certgen_certificate_config - class description

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

#ifndef CERTGEN_CERTIFICATE_CONFIG_H_INCLUDED
#define CERTGEN_CERTIFICATE_CONFIG_H_INCLUDED

namespace certgen
{

    class CertificateConfig
    {
        public:
            void deserialize (const cxxtools::SerializationInfo & si);
        private:
            std::string m_signatureType;
            uint32_t m_validity;
            int m_validityOffset;
            uint8_t m_certificateLevel;
    };

} // namescpace certgen

//  Self test of this class
 void
    certgen_certificate_config_test (bool verbose);

//  @end

#endif
