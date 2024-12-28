#include "cream_engine.hpp"

int main()
{
    CreamEngine ce;
    ce.LoadScriptFile("../scripts/test.lua");
    ce.Run();
}