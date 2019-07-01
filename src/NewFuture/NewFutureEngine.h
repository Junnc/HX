#pragma once
#include <memory>

#include "instance_shared_from_this.h"

class CNewFutureEngine : public CommonTools::instance_shared_from_this<CNewFutureEngine> {
public:
	// init newFuture engine
	bool Init();

	// run newFuture engine
	bool Run();
};
