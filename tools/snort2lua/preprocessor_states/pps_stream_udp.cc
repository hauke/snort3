/*
** Copyright (C) 2014 Cisco and/or its affiliates. All rights reserved.
 * Copyright (C) 2002-2013 Sourcefire, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License Version 2 as
 * published by the Free Software Foundation.  You may not use, modify or
 * distribute this program under any other version of the GNU General
 * Public License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
// pps_stream_udp.cc author Josh Rosenbaum <jrosenba@cisco.com>

#include <sstream>
#include <vector>

#include "conversion_state.h"
#include "utils/converter.h"
#include "utils/s2l_util.h"

namespace preprocessors
{

namespace {

class StreamUdp : public ConversionState
{
public:
    StreamUdp() : ConversionState() {};
    virtual ~StreamUdp() {};
    virtual bool convert(std::istringstream& data_stream);
};

} // namespace

bool StreamUdp::convert(std::istringstream& data_stream)
{

    bool retval = true;
    std::string keyword;

    table_api.open_table("stream_udp");

    while(data_stream >> keyword)
    {
        bool tmpval = true;

        if(keyword.back() == ',')
            keyword.pop_back();
        
        if(keyword.empty())
            continue;
        
        if(!keyword.compare("ignore_any_rules"))
            tmpval = table_api.add_option("ignore_any_rules", true);

        else if(!keyword.compare("timeout"))
        {
            table_api.add_diff_option_comment("timeout", "session_timeout");
            tmpval = parse_int_option("session_timeout", data_stream);
        }

        else
            tmpval = false;

        if (retval)
            retval = tmpval;
    }

    return retval;    
}

/**************************
 *******  A P I ***********
 **************************/

static ConversionState* ctor()
{
    return new StreamUdp();
}

static const ConvertMap preprocessor_stream_udp =
{
    "stream5_udp",
    ctor,
};

const ConvertMap* stream_udp_map = &preprocessor_stream_udp;

} // namespace preprocessors
