#include "glframwork/core.h"
#include <iostream>

void glmTest() {
	// 向量
	glm::vec2 v0(0);
	glm::vec3 v1(0);
	glm::vec4 v2(0);

	glm::vec4 vadd = v2 + glm::vec4(0);  // 向量加法

	auto mul = vadd * v2;  // 非点乘和叉乘, 只是对应元素相乘后放到对应位置
	auto dotRes = glm::dot(vadd, v2); // 向量点乘

	// 向量叉乘, glm只支持vec3的叉乘
	glm::vec3 vt0, vt1;
	auto crossRes = glm::cross(vt0, vt1);

	// 矩阵
	glm::mat4 m0(1.0); // 初始化一个4x4的单位矩阵
	glm::mat4 m1 = glm::identity<glm::mat4>();  // 使用identify定义一个单位矩阵

	glm::mat2 mm2(1.0);
	glm::mat3 mm3(1.0);
	glm::mat2x3 mm4(1.0);

	// 打印矩阵
	std::cout << glm::to_string(mm4) << std::endl;

	auto madd = m0 + m1;
	auto mmulti = m0 * m1;
	auto res = m0 * v2; // 矩阵与向量相乘

	// 转置矩阵
	auto transMat = glm::transpose(madd);

	// 逆矩阵
	auto inverseMat = glm::inverse(madd);
}
