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

/*
@header
    certgen_certificate_config -
@discuss
@end
*/

#include "fty_certificate_generator_classes.h"

//  Structure of our class

struct _certgen_certificate_config_t {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new certgen_certificate_config

certgen_certificate_config_t *
certgen_certificate_config_new (void)
{
    certgen_certificate_config_t *self = (certgen_certificate_config_t *) zmalloc (sizeof (certgen_certificate_config_t));
    assert (self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the certgen_certificate_config

void
certgen_certificate_config_destroy (certgen_certificate_config_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        certgen_certificate_config_t *self = *self_p;
        //  Free class properties here
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
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
certgen_certificate_config_test (bool verbose)
{
    printf (" * certgen_certificate_config: ");

    //  @selftest
    //  Simple create/destroy test
    certgen_certificate_config_t *self = certgen_certificate_config_new ();
    assert (self);
    certgen_certificate_config_destroy (&self);
    //  @end
    printf ("OK\n");
}
