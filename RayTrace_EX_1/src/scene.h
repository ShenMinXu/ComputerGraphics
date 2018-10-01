#pragma once
#ifndef DRAGON_CORE_SCENE
#define DRAGON_CORE_SCENE
#include"object.h"
#include"light.h"
#include<vector>
#include<memory>
namespace dragon {
	class Scene {
	public:
		std::vector<::std::shared_ptr<Object>>objs;
		std::vector<::std::shared_ptr<Light>>lights;
	};
}
#endif
