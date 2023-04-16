#pragma once
class W3_PongScene :
    public GameScene
{
public:
	W3_PongScene();
	~W3_PongScene() override = default;

	W3_PongScene(const W3_PongScene& other) = delete;
	W3_PongScene(W3_PongScene&& other) noexcept = delete;
	W3_PongScene& operator=(const W3_PongScene& other) = delete;
	W3_PongScene& operator=(W3_PongScene&& other) noexcept = delete;

protected:
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void OnGUI() override;
	void ResetLevel();

private:
	enum InputIds
	{
		MoveUpL,
		MoveDownL,
		MoveUpR,
		MoveDownR,
		Reset
	};
	float m_Speed{10 };
	float m_SpeedBall{ 2 };

	GameObject* m_pCubeLeft{};
	RigidBodyComponent* m_pRigidBodyLeft{};

	GameObject* m_pCubeRight{};
	RigidBodyComponent* m_pRigidBodyRight{};

	GameObject* m_pSphere{};
	RigidBodyComponent* m_pRigidBodySphere{};

	FixedCamera* m_pFixedCamera{};
	
	bool m_isGoingLeft{};

	bool m_isLeftGoingUp{};
	bool m_isLeftGoingDown{};

	bool m_isRightGoingUp{};
	bool m_isRightGoingDown{};

	

	XMFLOAT3 m_ballVelocity{};
};

