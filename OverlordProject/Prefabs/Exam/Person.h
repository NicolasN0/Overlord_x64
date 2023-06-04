#pragma once
#include "Scenegraph/GameObject.h"
#include <Materials\DiffuseMaterial_Skinned.h>
class Person :
    public GameObject
{
public:
	Person(int posX, int posZ);
	~Person() override = default;

	Person(const Person& other) = delete;
	Person(Person&& other) noexcept = delete;
	Person& operator=(const Person& other) = delete;
	Person& operator=(Person&& other) noexcept = delete;

protected:
	void Initialize(const SceneContext & sceneContext) override;
	void Update(const SceneContext & sceneContext) override;

private:
	DiffuseMaterial_Skinned* m_pMaterial{};


	int m_Width{};
	

	int m_PosX{};
	int m_PosZ{};



};

