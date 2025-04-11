#include "glframwork/core.h"
#include <iostream>

void glmTest() {
	// ����
	glm::vec2 v0(0);
	glm::vec3 v1(0);
	glm::vec4 v2(0);

	glm::vec4 vadd = v2 + glm::vec4(0);  // �����ӷ�

	auto mul = vadd * v2;  // �ǵ�˺Ͳ��, ֻ�Ƕ�ӦԪ����˺�ŵ���Ӧλ��
	auto dotRes = glm::dot(vadd, v2); // �������

	// �������, glmֻ֧��vec3�Ĳ��
	glm::vec3 vt0, vt1;
	auto crossRes = glm::cross(vt0, vt1);

	// ����
	glm::mat4 m0(1.0); // ��ʼ��һ��4x4�ĵ�λ����
	glm::mat4 m1 = glm::identity<glm::mat4>();  // ʹ��identify����һ����λ����

	glm::mat2 mm2(1.0);
	glm::mat3 mm3(1.0);
	glm::mat2x3 mm4(1.0);

	// ��ӡ����
	std::cout << glm::to_string(mm4) << std::endl;

	auto madd = m0 + m1;
	auto mmulti = m0 * m1;
	auto res = m0 * v2; // �������������

	// ת�þ���
	auto transMat = glm::transpose(madd);

	// �����
	auto inverseMat = glm::inverse(madd);
}
