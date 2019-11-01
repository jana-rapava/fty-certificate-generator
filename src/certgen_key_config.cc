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

#include "fty_certificate_generator_classes.h"

//  Structure of our class

struct _certgen_key_config_t {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new certgen_key_config

certgen_key_config_t *
certgen_key_config_new (void)
{
    certgen_key_config_t *self = (certgen_key_config_t *) zmalloc (sizeof (certgen_key_config_t));
    assert (self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the certgen_key_config

void
certgen_key_config_destroy (certgen_key_config_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        certgen_key_config_t *self = *self_p;
        //  Free class properties here
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

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
