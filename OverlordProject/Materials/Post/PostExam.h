#pragma once
#include "Misc/PostProcessingMaterial.h"
class PostExam :
    public PostProcessingMaterial
{
public:
	PostExam();
	~PostExam() override = default;
	PostExam(const PostExam& other) = delete;
	PostExam(PostExam&& other) noexcept = delete;
	PostExam& operator=(const PostExam& other) = delete;
	PostExam& operator=(PostExam&& other) noexcept = delete;

protected:
	void Initialize(const GameContext& /*gameContext*/) override {}
};

