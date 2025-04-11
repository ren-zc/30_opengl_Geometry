#include "geometry.h"
#include <vector>

Geometry::Geometry()
{

}

Geometry::~Geometry()
{
	if (mVao!=0)
	{
		glDeleteVertexArrays(1, &mVao);
	}
	if (mPosVbo!=0)
	{
		glDeleteBuffers(1, &mPosVbo);
	}
	if (mUvVbo!=0)
	{
		glDeleteBuffers(1, &mUvVbo);
	}
	if (mEbo!=0)
	{
		glDeleteBuffers(1, &mEbo);
	}
}

Geometry* Geometry::createBox(float size)
{
	Geometry* geometry = new Geometry();
	float halfSize = size / 2.0f;

	float vertices[] = {
		// ǰ�� (z = size / 2)
		-halfSize, -halfSize, halfSize,  // ����
		 halfSize, -halfSize, halfSize,  // ����
		 halfSize,  halfSize, halfSize,  // ����
		-halfSize,  halfSize, halfSize,  // ����

		// ���� (z = -size / 2)
		-halfSize, -halfSize, -halfSize, // ����
		 halfSize, -halfSize, -halfSize, // ����
		 halfSize,  halfSize, -halfSize, // ����
		-halfSize,  halfSize, -halfSize, // ����

		// ���� (x = -size / 2)
		-halfSize, -halfSize, -halfSize, // ����
		-halfSize, -halfSize,  halfSize, // ����
		-halfSize,  halfSize,  halfSize, // ����
		-halfSize,  halfSize, -halfSize, // ����

		// ���� (x = size / 2)
		 halfSize, -halfSize, -halfSize, // ����
		 halfSize, -halfSize,  halfSize, // ����
		 halfSize,  halfSize,  halfSize, // ����
		 halfSize,  halfSize, -halfSize, // ����

		 // ���� (y = size / 2)
		 -halfSize,  halfSize,  halfSize, // ����
		  halfSize,  halfSize,  halfSize, // ����
		  halfSize,  halfSize, -halfSize, // ����
		 -halfSize,  halfSize, -halfSize, // ����

		 // ���� (y = -size / 2)
		 -halfSize, -halfSize,  halfSize, // ����
		  halfSize, -halfSize,  halfSize, // ����
		  halfSize, -halfSize, -halfSize, // ����
		 -halfSize, -halfSize, -halfSize  // ����
	};

	float uvs[] = {
		// ǰ��
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		// ����
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		// ����
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		// ����
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		// ����
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		// ����
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		// ǰ��
		0, 1, 2, 2, 3, 0,
		// ����
		4, 5, 6, 6, 7, 4,
		// ����
		8, 9, 10, 10, 11, 8,
		// ����
		12, 13, 14, 14, 15, 12,
		// ����
		16, 17, 18, 18, 19, 16,
		// ����
		20, 21, 22, 22, 23, 20
	};


	geometry->mIndicesCount = 36;

	// ����vbo
	glGenBuffers(1, &geometry->mPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// uv vbo
	glGenBuffers(1, &geometry->mUvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	// ebo
	glGenBuffers(1, &geometry->mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// vao
	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);

	// ��VAO, ��д��VBO��������
	// Ϊ������һ�����õ�ϰ��, �˴���ð�һ��vbo
	glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVbo);  // λ��vbo
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVbo); // uv vbo
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	// ��EBO, ��ʵ������ǰ�EBO�󶨵���ǰ��VAO
	// EBO�������°�һ��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);

	// ���VAO
	glBindVertexArray(0);

	return geometry;
}

Geometry* Geometry::createSphere(float radius)
{
	Geometry* geometry = new Geometry();
	// 1. ��������
	int numLatlines = 60;  // γ������
	int numLonglines = 60;  // ��������

	std::vector<GLfloat> positions{};  // ��������
	std::vector<GLfloat> uvs{};  // uv��������
	std::vector<GLuint> indices{};  // ������������

	// 2. ��һ������ѭ������ pos uv, γ������, ��������
	for (int i = 0; i <= numLatlines; i++)
	{
		// �����Ż�����
		//float phi = i * glm::pi<float>() / (float)numLatlines;
		//float y = radius * cosf(phi);
		//float zx = radius * sinf(phi);
		//float thetaUnit = 2 * glm::pi<float>() / (float)numLonglines;
		//float v = 1.0 - (float)i / (float)numLatlines;
		for (int j = 0; j <= numLonglines; j++)
		{
			float phi = i * glm::pi<float>() / (float)numLatlines;
			float theta = j * 2 * glm::pi<float>() / (float)numLonglines;

			float y = radius * cosf(phi);
			float x = radius * sinf(phi) * cosf(theta);
			float z = radius * sinf(phi) * sinf(theta);

			positions.push_back(x);
			positions.push_back(y);
			positions.push_back(z);

			float u = 1.0 - (float)j / (float)numLonglines;  // !!!��Ҫ: ת��float
			float v = 1.0 - (float)i / (float)numLatlines;

			uvs.push_back(u);
			uvs.push_back(v);
		}
	}

	// 3. �ڶ�������ѭ������ indices, ���ѭ��û��=��, ��Ȼ����ѭ�����Ժϲ���
	for (int i = 0; i < numLatlines; i++)
	{
		for (int j = 0; j < numLonglines; j++) {
			int p1 = i * (numLonglines + 1) + j;
			int p2 = p1 + numLonglines + 1;
			int p3 = p1 + 1;
			int p4 = p2 + 1;

			indices.push_back(p1);
			indices.push_back(p2);
			indices.push_back(p3);
			indices.push_back(p3);
			indices.push_back(p2);
			indices.push_back(p4);
		}
	}

	// 4. vao vbo ebo
	// ����vbo
	glGenBuffers(1, &geometry->mPosVbo);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVbo);
	glBufferData(GL_ARRAY_BUFFER, positions.size()*sizeof(float), positions.data(), GL_STATIC_DRAW);

	// uv vbo
	glGenBuffers(1, &geometry->mUvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVbo);
	glBufferData(GL_ARRAY_BUFFER, uvs.size()*sizeof(float), uvs.data(), GL_STATIC_DRAW);

	// ebo
	glGenBuffers(1, &geometry->mEbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

	// vao
	glGenVertexArrays(1, &geometry->mVao);
	glBindVertexArray(geometry->mVao);

	// ��VAO, ��д��VBO��������
	// Ϊ������һ�����õ�ϰ��, �˴���ð�һ��vbo
	glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVbo);  // λ��vbo
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVbo); // uv vbo
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	// ��EBO, ��ʵ������ǰ�EBO�󶨵���ǰ��VAO
	// EBO�������°�һ��
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);

	// ���VAO
	glBindVertexArray(0);

	// ��������
	geometry->mIndicesCount = indices.size();

	return geometry;
}
