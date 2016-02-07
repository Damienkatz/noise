//
//  results.hpp
//  noise
//
//  Created by Damien Katz on 2/5/16.
//  Copyright © 2016 Damien Katz. All rights reserved.
//

#ifndef results_hpp
#define results_hpp

#include <stdio.h>
#include "noise.h"

namespace_Noise

struct DocResult {
    std::string id;
    std::list<std::vector<uint64_t> > array_paths;

    void TruncateArrayPaths(size_t array_path_depth);
    bool IntersectArrayPaths(const DocResult& other);
};

class Results {
    std::unique_ptr<QueryRuntimeFilter> filter;
    bool first_has_been_called = false;

    Results(std::unique_ptr<QueryRuntimeFilter>& _filter) :
        filter(std::move(_filter)) {}

    std::string GetNext() {
        static std::string emptystr("");
        std::unique_ptr<DocResult> dr;
        if (!first_has_been_called) {
            first_has_been_called = true;

            dr = filter->FirstResult(emptystr);
        } else {
            dr = filter->NextResult();
        }

        return dr ? dr->id : emptystr;
    }
};

namespace_Noise_end

#endif /* results_hpp */
