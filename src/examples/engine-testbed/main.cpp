#include <core/logger.h>
#include <core/assert.h>

int main()
{
	Log::Init();

    LOG_WARN("Du er kul");
	ENGINE_ASSERT(false);
    return 0;
}