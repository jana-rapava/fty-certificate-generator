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

struct _certgen_certificate_generator_server_t {
    int filler;     //  Declare class properties here
};


//  --------------------------------------------------------------------------
//  Create a new certgen_certificate_generator_server

certgen_certificate_generator_server_t *
certgen_certificate_generator_server_new (void)
{
    certgen_certificate_generator_server_t *self = (certgen_certificate_generator_server_t *) zmalloc (sizeof (certgen_certificate_generator_server_t));
    assert (self);
    //  Initialize class properties here
    return self;
}


//  --------------------------------------------------------------------------
//  Destroy the certgen_certificate_generator_server

void
certgen_certificate_generator_server_destroy (certgen_certificate_generator_server_t **self_p)
{
    assert (self_p);
    if (*self_p) {
        certgen_certificate_generator_server_t *self = *self_p;
        //  Free class properties here
        //  Free object itself
        free (self);
        *self_p = NULL;
    }
}

