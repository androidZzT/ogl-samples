#include "test.hpp"

namespace
{
	char const* VERT_SHADER_SOURCE("gl-320/glsl-uniform-align.vert");
	char const* FRAG_SHADER_SOURCE("gl-320/glsl-uniform-align.frag");
	char const* TEXTURE_DIFFUSE("kueken7_rgba8_srgb.dds");

	GLsizei const VertexCount(4);
	GLsizeiptr const VertexSize = VertexCount * sizeof(glf::vertex_v2fv2f);
	glf::vertex_v2fv2f const VertexData[VertexCount] =
	{
		glf::vertex_v2fv2f(glm::vec2(-1.0f,-1.0f), glm::vec2(0.0f, 1.0f)),
		glf::vertex_v2fv2f(glm::vec2( 1.0f,-1.0f), glm::vec2(1.0f, 1.0f)),
		glf::vertex_v2fv2f(glm::vec2( 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
		glf::vertex_v2fv2f(glm::vec2(-1.0f, 1.0f), glm::vec2(0.0f, 0.0f))
	};

	GLsizei const ElementCount(6);
	GLsizeiptr const ElementSize = ElementCount * sizeof(GLushort);
	GLushort const ElementData[ElementCount] =
	{
		0, 1, 2, 
		2, 3, 0
	};

	namespace buffer
	{
		enum type
		{
			VERTEX,
			ELEMENT,
			TRANSFORM,
			MAX
		};
	}//namespace buffer

	GLuint VertexArrayName(0);
	GLuint ProgramName(0);
	GLuint TextureName(0);
	std::vector<GLuint> BufferName(buffer::MAX);

	GLint UniformTransform(0);
	GLint UniformDiffuse(0);
}//namespace

class sample : public framework
{
public:
	sample(int argc, char* argv[]) :
		framework(argc, argv, "gl-320-glsl-uniform-align", framework::CORE, 3, 2)
	{}

private:
	bool initProgram()
	{
		bool Validated(true);
	
		if(Validated)
		{
			compiler Compiler;
			GLuint VertShaderName = Compiler.create(GL_VERTEX_SHADER, getDataDirectory() + VERT_SHADER_SOURCE, "--version 150 --profile core");
			GLuint FragShaderName = Compiler.create(GL_FRAGMENT_SHADER, getDataDirectory() + FRAG_SHADER_SOURCE, "--version 150 --profile core");
			Validated = Validated && Compiler.check();

			ProgramName = glCreateProgram();
			glAttachShader(ProgramName, VertShaderName);
			glAttachShader(ProgramName, FragShaderName);

			glBindAttribLocation(ProgramName, semantic::attr::POSITION, "Position");
			glBindAttribLocation(ProgramName, semantic::attr::TEXCOORD, "Texcoord");
			glBindFragDataLocation(ProgramName, semantic::frag::COLOR, "Color");
			glLinkProgram(ProgramName);
			Validated = Validated && Compiler.check_program(ProgramName);
		}

		if(Validated)
		{
			UniformTransform = glGetUniformBlockIndex(ProgramName, "transform");
			UniformDiffuse = glGetUniformLocation(ProgramName, "Diffuse");
		}

		if(Validated)
		{
			GLint UniformTest0 = glGetUniformBlockIndex(ProgramName, "test0");

			GLint BlockDataSize = 0;
			glGetActiveUniformBlockiv(ProgramName, UniformTest0, GL_UNIFORM_BLOCK_DATA_SIZE, &BlockDataSize);

			// D3D returns 32, GL returns 32
			Validated = Validated && BlockDataSize == 32;
		}

		if (Validated)
		{
			GLint UniformTest1 = glGetUniformBlockIndex(ProgramName, "test1");

			GLint BlockDataSize = 0;
			glGetActiveUniformBlockiv(ProgramName, UniformTest1, GL_UNIFORM_BLOCK_DATA_SIZE, &BlockDataSize);

			// D3D returns 40, GL returns 48
			Validated = Validated && BlockDataSize == 48;
		}

		if (Validated)
		{
			GLint UniformTest1 = glGetUniformBlockIndex(ProgramName, "test1b");

			GLint BlockDataSize = 0;
			glGetActiveUniformBlockiv(ProgramName, UniformTest1, GL_UNIFORM_BLOCK_DATA_SIZE, &BlockDataSize);

			// D3D returns 32, GL returns 32
			Validated = Validated && BlockDataSize == 32;
		}

		if (Validated)
		{
			GLint UniformTest = glGetUniformBlockIndex(ProgramName, "test2");

			GLint BlockDataSize = 0;
			glGetActiveUniformBlockiv(ProgramName, UniformTest, GL_UNIFORM_BLOCK_DATA_SIZE, &BlockDataSize);

			assert(BlockDataSize == 16);
			Validated = Validated && BlockDataSize == 16;
		}

		if (Validated)
		{
			GLint UniformTest = glGetUniformBlockIndex(ProgramName, "test3");

			GLint BlockDataSize = 0;
			glGetActiveUniformBlockiv(ProgramName, UniformTest, GL_UNIFORM_BLOCK_DATA_SIZE, &BlockDataSize);

			// D3D returns 16, GL returns 32
			Validated = Validated && BlockDataSize == 32;
		}

		if (Validated)
		{
			GLint UniformTest = glGetUniformBlockIndex(ProgramName, "test4");

			GLint BlockDataSize = 0;
			glGetActiveUniformBlockiv(ProgramName, UniformTest, GL_UNIFORM_BLOCK_DATA_SIZE, &BlockDataSize);

			// D3D returns 32, GL returns 32
			Validated = Validated && BlockDataSize == 32;
		}

		if (Validated)
		{
			GLint UniformTest = glGetUniformBlockIndex(ProgramName, "test5");

			GLint BlockDataSize = 0;
			glGetActiveUniformBlockiv(ProgramName, UniformTest, GL_UNIFORM_BLOCK_DATA_SIZE, &BlockDataSize);

			assert(BlockDataSize == 16);
			Validated = Validated && BlockDataSize == 16;
		}

		if (Validated)
		{
			GLint UniformTest = glGetUniformBlockIndex(ProgramName, "test6");

			GLint BlockDataSize = 0;
			glGetActiveUniformBlockiv(ProgramName, UniformTest, GL_UNIFORM_BLOCK_DATA_SIZE, &BlockDataSize);

			// D3D returns 16, GL returns 32
			Validated = Validated && BlockDataSize == 32;
		}

		if (Validated)
		{
			GLint UniformTest = glGetUniformBlockIndex(ProgramName, "test7");

			GLint BlockDataSize = 0;
			glGetActiveUniformBlockiv(ProgramName, UniformTest, GL_UNIFORM_BLOCK_DATA_SIZE, &BlockDataSize);

			// D3D returns 32, GL returns 32
			Validated = Validated && BlockDataSize == 32;
		}

		if (Validated)
		{
			GLint UniformTest = glGetUniformBlockIndex(ProgramName, "test8");

			GLint BlockDataSize = 0;
			glGetActiveUniformBlockiv(ProgramName, UniformTest, GL_UNIFORM_BLOCK_DATA_SIZE, &BlockDataSize);

			// D3D returns 48, GL returns 48
			Validated = Validated && BlockDataSize == 48;
		}

		if (Validated)
		{
			GLint UniformTest = glGetUniformBlockIndex(ProgramName, "test9");

			GLint BlockDataSize = 0;
			glGetActiveUniformBlockiv(ProgramName, UniformTest, GL_UNIFORM_BLOCK_DATA_SIZE, &BlockDataSize);

			// D3D returns 48, GL returns 48
			Validated = Validated && BlockDataSize == 48;
		}

		if (Validated)
		{
			GLint UniformTest = glGetUniformBlockIndex(ProgramName, "test10");

			GLint BlockDataSize = 0;
			glGetActiveUniformBlockiv(ProgramName, UniformTest, GL_UNIFORM_BLOCK_DATA_SIZE, &BlockDataSize);

			// D3D returns 48, GL returns 48
			Validated = Validated && BlockDataSize == 48;
		}

		return Validated && this->checkError("initProgram");
	}

	bool initBuffer()
	{
		glGenBuffers(buffer::MAX, &BufferName[0]);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, ElementSize, ElementData, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
		glBufferData(GL_ARRAY_BUFFER, VertexSize, VertexData, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		GLint UniformBufferOffset(0);
		glGetIntegerv(GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT, &UniformBufferOffset);
		GLint UniformBlockSize = glm::max(GLint(sizeof(glm::mat4)), UniformBufferOffset);

		glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
		glBufferData(GL_UNIFORM_BUFFER, UniformBlockSize, NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);

		return this->checkError("initBuffer");;
	}

	bool initTexture()
	{
		gli::gl GL(gli::gl::PROFILE_GL32);
		gli::texture2d Texture(gli::load_dds((getDataDirectory() + TEXTURE_DIFFUSE).c_str()));
		assert(!Texture.empty());

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		glGenTextures(1, &TextureName);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureName);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, GLint(Texture.levels() - 1));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		gli::gl::format const Format = GL.translate(Texture.format(), Texture.swizzles());
		for(gli::texture2d::size_type Level = 0; Level < Texture.levels(); ++Level)
		{
			glTexImage2D(GL_TEXTURE_2D, GLint(Level),
				Format.Internal,
				GLsizei(Texture[Level].extent().x), GLsizei(Texture[Level].extent().y),
				0,
				Format.External, Format.Type,
				Texture[Level].data());
		}

		if(Texture.levels() == 1)
			glGenerateMipmap(GL_TEXTURE_2D);
	
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

		return this->checkError("initTexture");
	}

	bool initVertexArray()
	{
		glGenVertexArrays(1, &VertexArrayName);
		glBindVertexArray(VertexArrayName);
			glBindBuffer(GL_ARRAY_BUFFER, BufferName[buffer::VERTEX]);
			glVertexAttribPointer(semantic::attr::POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), BUFFER_OFFSET(0));
			glVertexAttribPointer(semantic::attr::TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(glf::vertex_v2fv2f), BUFFER_OFFSET(sizeof(glm::vec2)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glEnableVertexAttribArray(semantic::attr::POSITION);
			glEnableVertexAttribArray(semantic::attr::TEXCOORD);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, BufferName[buffer::ELEMENT]);
		glBindVertexArray(0);

		return this->checkError("initVertexArray");
	}

	bool begin()
	{
		bool Validated = true;

		if(Validated)
			Validated = initTexture();
		if(Validated)
			Validated = initProgram();
		if(Validated)
			Validated = initBuffer();
		if(Validated)
			Validated = initVertexArray();

		return Validated && this->checkError("begin");
	}

	bool end()
	{
		glDeleteBuffers(buffer::MAX, &BufferName[0]);
		glDeleteProgram(ProgramName);
		glDeleteTextures(1, &TextureName);
		glDeleteVertexArrays(1, &VertexArrayName);

		return this->checkError("end");
	}

	bool render()
	{
		glm::ivec2 WindowSize(this->getWindowSize());

		{
			glBindBuffer(GL_UNIFORM_BUFFER, BufferName[buffer::TRANSFORM]);
			glm::mat4* Pointer = (glm::mat4*)glMapBufferRange(
				GL_UNIFORM_BUFFER, 0,	sizeof(glm::mat4),
				GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

			glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.0f);
			glm::mat4 Model = glm::mat4(1.0f);
		
			*Pointer = Projection * this->view() * Model;

			// Make sure the uniform buffer is uploaded
			glUnmapBuffer(GL_UNIFORM_BUFFER);
		}

		glViewport(0, 0, WindowSize.x, WindowSize.y);
		glClearBufferfv(GL_COLOR, 0, &glm::vec4(1.0f, 0.5f, 0.0f, 1.0f)[0]);

		glUseProgram(ProgramName);
		glUniform1i(UniformDiffuse, 0);
		glUniformBlockBinding(ProgramName, UniformTransform, semantic::uniform::TRANSFORM0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureName);
		glBindVertexArray(VertexArrayName);
		glBindBufferBase(GL_UNIFORM_BUFFER, semantic::uniform::TRANSFORM0, BufferName[buffer::TRANSFORM]);

		glDrawElementsInstancedBaseVertex(GL_TRIANGLES, ElementCount, GL_UNSIGNED_SHORT, 0, 1, 0);

		return true;
	}
};

int main(int argc, char* argv[])
{
	int Error = 0;

	sample Sample(argc, argv);
	Error += Sample();

	return Error;
}

