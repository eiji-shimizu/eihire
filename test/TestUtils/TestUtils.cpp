#include "TestUtils.h"

namespace Eihire::TestUtils {

    std::filesystem::path getTestDataPath()
    {
        std::filesystem::path p = std::filesystem::current_path();
        std::filesystem::path root = p.root_path();
        while (p != root) {
            p = p.parent_path();
            if (p.filename() == "eihire") {
                break;
            }
        }
        if (p == root)
            throw std::exception("can't find testdata directory.");
        p.append("test").append("testdata");
        return p;
    }

} // namespace Eihire::TestUtils
