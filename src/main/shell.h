/*
** Copyright (C) 2014 Cisco and/or its affiliates. All rights reserved.
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License Version 2 as
** published by the Free Software Foundation.  You may not use, modify or
** distribute this program under any other version of the GNU General
** Public License.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/
// shell.h author Russ Combs <rucombs@cisco.com>

#ifndef SHELL_H
#define SHELL_H

#include <string>

class Shell
{
public:
    Shell(const char* file = nullptr);
    ~Shell();

    void configure(struct SnortConfig*);
    void configure(struct SnortConfig*, const char* file);

    void set_overrides(const char*);
    void install(const char*, const struct luaL_Reg*);
    void execute(const char*, std::string&);

private:
    struct lua_State* lua;
    std::string file;
    std::string overrides;
};

#endif

