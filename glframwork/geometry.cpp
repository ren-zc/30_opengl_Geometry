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
		// 前面 (z = size / 2)
		-halfSize, -halfSize, halfSize,  // 左下
		 halfSize, -halfSize, halfSize,  // 右下
		 halfSize,  halfSize, halfSize,  // 右上
		-halfSize,  halfSize, halfSize,  // 左上

		// 后面 (z = -size / 2)
		-halfSize, -halfSize, -halfSize, // 左下
		 halfSize, -halfSize, -halfSize, // 右下
		 halfSize,  halfSize, -halfSize, // 右上
		-halfSize,  halfSize, -halfSize, // 左上

		// 左面 (x = -size / 2)
		-halfSize, -halfSize, -halfSize, // 左下
		-halfSize, -halfSize,  halfSize, // 右下
		-halfSize,  halfSize,  halfSize, // 右上
		-halfSize,  halfSize, -halfSize, // 左上

		// 右面 (x = size / 2)
		 halfSize, -halfSize, -halfSize, // 左下
		 halfSize, -halfSize,  halfSize, // 右下
		 halfSize,  halfSize,  halfSize, // 右上
		 halfSize,  halfSize, -halfSize, // 左上

		 // 上面 (y = size / 2)
		 -halfSize,  halfSize,  halfSize, // 左下
		  halfSize,  halfSize,  halfSize, // 右下
		  halfSize,  halfSize, -halfSize, // 右上
		 -halfSize,  halfSize, -halfSize, // 左上

		 // 下面 (y = -size / 2)
		 -halfSize, -halfSize,  halfSize, // 左下
		  halfSize, -halfSize,  halfSize, // 右下
		  halfSize, -halfSize, -halfSize, // 右上
		 -halfSize, -halfSize, -halfSize  // 左上
	};

	float uvs[] = {
		// 前面
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		// 后面
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		// 左面
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		// 右面
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		// 上面
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
		// 下面
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		// 前面
		0, 1, 2, 2, 3, 0,
		// 后面
		4, 5, 6, 6, 7, 4,
		// 左面
		8, 9, 10, 10, 11, 8,
		// 右面
		12, 13, 14, 14, 15, 12,
		// 上面
		16, 17, 18, 18, 19, 16,
		// 下面
		20, 21, 22, 22, 23, 20
	};


	geometry->mIndicesCount = 36;

	// 顶点vbo
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

	// 绑定VAO, 并写入VBO属性数据
	// 为了养成一个良好的习惯, 此处最好绑定一次vbo
	glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVbo);  // 位置vbo
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVbo); // uv vbo
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	// 绑定EBO, 其实意义就是把EBO绑定到当前的VAO
	// EBO必须重新绑定一次
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);

	// 解绑VAO
	glBindVertexArray(0);

	return geometry;
}

Geometry* Geometry::createSphere(float radius)
{
	Geometry* geometry = new Geometry();
	// 1. 声明变量
	int numLatlines = 60;  // 纬线数量
	int numLonglines = 60;  // 经线数量

	std::vector<GLfloat> positions{};  // 顶点数组
	std::vector<GLfloat> uvs{};  // uv坐标数组
	std::vector<GLuint> indices{};  // 顶点索引数组

	// 2. 第一次两层循环生成 pos uv, 纬线在外, 经线在内
	for (int i = 0; i <= numLatlines; i++)
	{
		// 代码优化部分
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

			float u = 1.0 - (float)j / (float)numLonglines;  // !!!重要: 转成float
			float v = 1.0 - (float)i / (float)numLatlines;

			uvs.push_back(u);
			uvs.push_back(v);
		}
	}

	// 3. 第二次两层循环生成 indices, 这次循环没有=号, 不然两个循环可以合并了
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
	// 顶点vbo
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

	// 绑定VAO, 并写入VBO属性数据
	// 为了养成一个良好的习惯, 此处最好绑定一次vbo
	glBindBuffer(GL_ARRAY_BUFFER, geometry->mPosVbo);  // 位置vbo
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, geometry->mUvVbo); // uv vbo
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

	// 绑定EBO, 其实意义就是把EBO绑定到当前的VAO
	// EBO必须重新绑定一次
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->mEbo);

	// 解绑VAO
	glBindVertexArray(0);

	// 索引数量
	geometry->mIndicesCount = indices.size();

	return geometry;
}
