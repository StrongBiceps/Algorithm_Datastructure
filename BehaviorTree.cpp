#include <random>
#include "pch.h"
#include "BehaviorTree.h"

std::random_device rd;
std::mt19937_64 mt(rd());
std::uniform_int_distribution<int> dist(0, 100);

bool TXT_AI::BehaviorTree::node::SelectorSuccess = false;
bool TXT_AI::BehaviorTree::bSoftLearned = false;
bool TXT_AI::BehaviorTree::bLogiLearned = false;
bool TXT_AI::BehaviorTree::IsSkillBlocked = false;
bool TXT_AI::BehaviorTree::IsAttackBlocked = false;

//�Ʒ� �������� static���� �����ϸ� �� ȿ�������� �����丵�� �� �ִ�.
//�ٸ� ���鿡 ������ SetSKillType�̳� SetEnemy�� ���� �ʰ� ���� ������ Ȱ���� �� ���� ������ ���δ�.
//������ ���� ������ �ش� �������� �ٽ� Reset�ϸ� �ȴ�.
//static�̱� ������ ��� BehaviorTree��ü�鵵 ���� �����ϹǷ� Reset���� ������ ���� ���޵Ǿ� �ǵ�ġ ���� ������ �߻��Ѵ�.
//Enemy* Enemyobj = nullptr;
//bool bSkillUsed = false;
//bool bSkillType = false;

TXT_AI::BehaviorTree::node::node()
{
	NType = Node_Type::NT_Default;
}

TXT_AI::BehaviorTree::node::~node()
{
	//delete _Enemyobj;

	for (const auto& i : nodes)
	{
		delete i;
	}

	for (const auto& i : Conditions)
	{
		delete i;
	}
}

TXT_AI::BehaviorTree::Node_Type TXT_AI::BehaviorTree::node::Get_NType() const
{
	return NType;
}

TXT_AI::BehaviorTree::ActionNode::ActionNode()
{
	NType = Node_Type::NT_Action;
}

TXT_AI::BehaviorTree::Decorator::Decorator()
{
	NType = Node_Type::NT_Decorator;
}

TXT_AI::BehaviorTree::SelectorNode::SelectorNode()
{
	NType = Node_Type::NT_Selector;
}

bool TXT_AI::BehaviorTree::SelectorNode::Execute()
{
	if (SelectorSuccess == true)
	{
		//Selector boolean set(success) from lower node
		SelectorSuccess = false;
		return true;
	}

	for (node* child : nodes)
	{
		if (SelectorSuccess == true)
		{
			//Selector boolean set(success) from lower node
			return true;
		}

		switch (static_cast<int>(child->Get_NType()))
		{
		case 0:
		{
			child->Execute();
			break;
		}
		case 1:
		{
			bool bOverall = child->checking_conditions();
			if (bOverall == false)
			{
				continue;
			}
			child->Execute();
			break;
		}
		case 2:
		{
			child->Execute();
			break;
		}
		default:
		{
			assert(static_cast<int>(child->Get_NType()) < 0 ||
				static_cast<int>(child->Get_NType()) > 2);
			return false;
		}
		}
	}
	return false;
}

TXT_AI::BehaviorTree::SequenceNode::SequenceNode()
{
	NType = Node_Type::NT_Sequence;
}

bool TXT_AI::BehaviorTree::SequenceNode::Execute()
{
	for (node* child : nodes) {
		switch (static_cast<int>(child->Get_NType()))
		{
		case 0:
		{
			child->Execute();
			break;
		}
		case 1:
		{
			bool bOverall = child->checking_conditions();
			if (bOverall == false)
			{
				continue;
			}
			child->Execute();
			break;
		}
		case 2:
		{
			child->Execute();
			break;
		}
		default:
		{
			assert(static_cast<int>(child->Get_NType()) < 0 ||
				static_cast<int>(child->Get_NType()) > 2);
			return false;
		}
		}
	}
	return false;
}

bool TXT_AI::BehaviorTree::SequenceNode::checking_conditions()
{
	bool bOverall = true;

	for (register int i = 0; i < Conditions.size(); ++i)
	{
		bOverall = Conditions[i]->Check();
		if (bOverall == false)
		{
			return false;
		}
	}

	return true;
}

TXT_AI::BehaviorTree::RootNode::RootNode()
{
	NType = Node_Type::NT_Root;
}

bool TXT_AI::BehaviorTree::RootNode::Execute()
{
	for (node* child : nodes) {
		switch (static_cast<int>(child->Get_NType()))
		{
		case 0:
		{
			child->Execute();
			break;
		}
		case 1:
		{
			bool bOverall = child->checking_conditions();
			if (bOverall == false)
			{
				continue;
			}
			child->Execute();
			break;
		}
		case 2:
		{
			child->Execute();
			break;
		}
		default:
		{
			assert(static_cast<int>(child->Get_NType()) < 0 ||
				static_cast<int>(child->Get_NType()) > 2);
			return false;
		}
		}
	}
	SelectorSuccess = false;
	return false;
}

TXT_AI::BehaviorTree::BehaviorTree()
{
	root = new RootNode();
	bSkillUsed = false;
	bSkillType = true;

	SoftR=new SoftmaxRegression;
	LogR = new LogisticRegression;
}

//TXT_AI::BehaviorTree::BehaviorTree(BehaviorTree& _BTree_Param)
//{
//	//root = _BTree_Param.GetRoot();
//}

TXT_AI::BehaviorTree::~BehaviorTree()
{
	delete root;
	root = nullptr;

	delete SoftR;
	SoftR = nullptr;

	delete LogR;
	LogR = nullptr;
}


bool TXT_AI::BehaviorTree::Initiate_BTree()
{
	IsSkillBlocked = false;
	IsAttackBlocked = false;
	root->Execute();
	return true;
}

//BehaviorTree �ϳ��� Enemy �ϳ��� �Ҵ�ǹǷ� �� Ŭ������ Enemy ������ ���ƾ� �Ѵ�.
void TXT_AI::BehaviorTree::Init_BTree(Enemy* _Enemy)
{
	//�� ����� �����ڰ� � Enemy���� Setting�� ����� �Ѵ�.

	Enemyobj = _Enemy;

	if (root == nullptr)
	{
		root = new RootNode();
	}
	else
	{
		for (const auto& i : root->GetSubTree())
		{
			delete i;
		}
		root->GetSubTree().clear();
	}

	//root node �ڽ� 1��
	root->AddChild(new Selector_1());
	//root->SetEnemy(Enemyobj);

	//Attack Selector
	auto _Selector_1 = root->GetSubTree()[0];
	//selector �ڽ� 3��
	_Selector_1->AddChild(new BlockMagicSkill());
	_Selector_1->AddChild(new BlockSkill());
	_Selector_1->AddChild(new AttackCharacter());
	_Selector_1->AddChild(new BlockCharacter());

	//Block Magic Skill Sequence
	auto _SoftBlockSkill_Seq = _Selector_1->GetSubTree()[0];
	auto _IsMagicSkillUsed = new IsMagicSkillUsed();
	_IsMagicSkillUsed->SetSkillType(bSkillType);
	_IsMagicSkillUsed->SetSkillUsed(bSkillUsed);
	_SoftBlockSkill_Seq->AddDecorator(new SkillBlockprob());
	_SoftBlockSkill_Seq->AddDecorator(_IsMagicSkillUsed);
	auto _MagicSkillBlockNode = new MagicSkillBlock();
	_MagicSkillBlockNode->SetSoftR(SoftR);
	_MagicSkillBlockNode->SetLogR(LogR);
	_MagicSkillBlockNode->SetEnemy(Enemyobj);
	_MagicSkillBlockNode->SetSkillType(bSkillType);
	_MagicSkillBlockNode->SetSkillUsed(bSkillUsed);
	_SoftBlockSkill_Seq->AddChild(_MagicSkillBlockNode);

	//Block Skill sequence
	auto _BlockSkill_Seq = _Selector_1->GetSubTree()[1];
	auto _IsSkillUsed = new IsSkillUsed();
	_IsSkillUsed->SetSkillType(bSkillType);
	_IsSkillUsed->SetSkillUsed(bSkillUsed);
	_BlockSkill_Seq->AddDecorator(new SkillBlockprob);
	_BlockSkill_Seq->AddDecorator(_IsSkillUsed);
	auto _SkillBlockNode = new SkillBlock;
	_SkillBlockNode->SetSoftR(SoftR);
	_SkillBlockNode->SetLogR(LogR);
	_SkillBlockNode->SetEnemy(Enemyobj);
	_SkillBlockNode->SetSkillType(bSkillType);
	_SkillBlockNode ->SetSkillUsed(bSkillUsed);
	_BlockSkill_Seq->AddChild(_SkillBlockNode);

	//Attack Sequence
	auto _AttackCharacter_Seq = _Selector_1->GetSubTree()[2];
	auto _AttackNode = new AttackNode();
	_AttackNode->SetEnemy(Enemyobj);

	//_AttackCharacter_Seq->AddChild(new AttackNode());
	_AttackCharacter_Seq->AddChild(_AttackNode);
	_AttackCharacter_Seq->AddDecorator(new HealthLowNode());
	//Block chance
	_AttackCharacter_Seq->AddDecorator(new AttackorBlock());

	//Block Node adding
	auto _BlockCharacter_Seq = _Selector_1->GetSubTree()[3];
	auto _BlockNode = new BlockNode();
	_BlockNode->SetEnemy(Enemyobj);
	_BlockCharacter_Seq->AddChild(_BlockNode);
}

std::vector<TXT_AI::dataType> TXT_AI::SoftmaxRegression::softmax(const std::vector<dataType>& z)
{
	std::vector<dataType> exp_z;
	std::vector<dataType> result;
	dataType exp_sum = 0.0;

	for (dataType val : z)
	{
		exp_z.push_back(std::exp(val));
		//�и�� �� exp���� ���̴�.
		exp_sum += std::exp(val);
	}

	for (dataType exp_val : exp_z)
	{
		//result�� �� Ȯ���� ���̴�.
		result.push_back(exp_val / exp_sum);
	}

	return result;
}

TXT_AI::dataType TXT_AI::SoftmaxRegression::crossEntropyLoss(const std::vector<dataType>& predicted_probs, int true_label)
{
	if (true_label < 0 || true_label >= num_classes)
	{
		throw std::runtime_error("Invalid true_label value");
	}

	return -std::log(predicted_probs[true_label]);
}

void TXT_AI::SoftmaxRegression::SoftmaxRegression_training(std::vector<dataType>& X, std::vector<int>& Y, std::vector<std::vector<dataType>>& weights, int epochs, double lr)
{
	const int m = X.size();

	if (m != Y.size()) throw std::runtime_error("Except occured");

	for (int epoch = 0; epoch < epochs; ++epoch)
	{
		for (int i = 0; i < m; ++i)
		{
			std::vector<dataType> z(num_classes, 0.0);

			for (int j = 0; j < num_classes; ++j)
			{
				for (int k = 0; k < num_features; ++k)
				{
					z[j] += weights[k][j] * X[i];
				}
			}

			std::vector<dataType> probs = softmax(z);
			int true_label = Y[i];
			dataType loss = crossEntropyLoss(probs, true_label);
			for (int j = 0; j < num_classes; ++j)
			{
				for (int k = 0; k < num_features; ++k)
				{
					weights[k][j] -= lr * (probs[j] - (j == true_label)) * X[i];
				}
			}
		}
	}
}

void TXT_AI::SoftmaxRegression::Initiate_SoftmaxRegression()
{
	init_vector();

	//����ġ 1*3���
	std::vector<std::vector<dataType>> weights(num_features, std::vector<dataType>(num_classes, 0.0));

	SoftmaxRegression_training(X, Y, weights, 5000, learning_rate);

	// ����
	dataType nX = 11;
	std::vector<dataType> z(num_classes, 0.0);
	for (int j = 0; j < num_classes; ++j)
	{
		for (int k = 0; k < num_features; ++k)
		{
			z[j] += weights[k][j] * nX;
		}
	}
	std::vector<dataType> probs = softmax(z);

	ipredict = std::distance(probs.begin(), std::max_element(probs.begin(), probs.end()));
	std::cout << "���� ���� : " << ipredict+1<<" �� ��ų" << '\n';

}

TXT_AI::SoftmaxRegression::SoftmaxRegression()
{
	X.reserve(10);
	//Y.reserve(10);
}

void TXT_AI::SoftmaxRegression::init_vector()
{
	X = { 1,2,3,4,5,6,7,8,9,10 };
	//Y = { 0, 0, 1, 2, 3, 3, 2, 3, 3, 3 };
}

TXT_AI::LogisticRegression::LogisticRegression()
{
	X.reserve(10);
	//Y.reserve(10);
}

double TXT_AI::LogisticRegression::sigmoid(double z)
{
	return 1.0 / (1.0 + std::exp(-z));
}

double TXT_AI::LogisticRegression::GradientDescent(std::vector<dataType>& X, std::vector<dataType>& Y, double& W, double& b, double lr)
{
	const int m = Y.size();
	double loss = 0, dW = 0, db = 0;

	if (m != X.size()) throw std::runtime_error("Except occured");

	for (int i = 0; i < m; ++i)
	{
		double H = sigmoid(W * X[i] + b);

		dW += (H - Y[i]) * X[i];
		db += H - Y[i];
	}

	dW = dW / m;

	db = db / m;

	for (int i = 0; i < m; ++i)
	{
		double H = sigmoid(W * X[i] + b);

		loss += (Y[i] * std::log(H) + (1 - Y[i]) * std::log(1 - H));
	}

	W = W - lr * dW;
	b = b - lr * db;

	loss = loss * -1 / m;

	return loss;
}

void TXT_AI::LogisticRegression::LogisticRegression_training(std::vector<dataType>& X, std::vector<dataType>& Y, double& W, double& b, int epochs, double lr)
{
	int printTry = epochs / 10;

	for (int i = 0; i < epochs; ++i)
	{
		double loss = GradientDescent(X, Y, W, b, lr);
		//if (i % printTry == 0) std::cout << "Weight: " << W << ", Bias: " << b << ", Loss: " << loss << '\n';
	}
}

double TXT_AI::LogisticRegression::predict(double& W, double& b, dataType X)
{
	return (sigmoid(W * X + b) < 0.5) ? 0 : 1;
}

void TXT_AI::LogisticRegression::init_vector()
{
	X = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	//Y = { 0,0,0,0,0,1,1,0,0,0 };
}

void TXT_AI::LogisticRegression::initiate_LogisticRegression()
{
	init_vector();

	double W = 12; // random value
	double b = 12; // random value

	// train 5000 times
	LogisticRegression_training(X, Y, W, b, 5000, learning_rate);
	// prediction
	const int nX = 11;
	ipredict = predict(W, b, nX);
	std::cout << "���� ���� :" << ipredict+1<<" �� ��ų" << std::endl;
}

bool TXT_AI::BehaviorTree::AttackorBlock::Check()
{
	auto prob = dist(mt);

	if (prob >= 30)
	{
		//����
		return true;
	}
	else
	{
		SelectorSuccess = false;
		return false;
	}
}

bool TXT_AI::BehaviorTree::HealthLowNode::Check()
{
	// �����δ� ü���� ������ Ȯ���ϴ� ������ �����ؾ� ��
	//std::cout << "ĳ������ ü���� 0�� �ƴϴ�." << std::endl;
	return true;
}

// bool TXT_AI::BehaviorTree::SelectorNode::AbortCheck()
// {

// }

bool TXT_AI::BehaviorTree::AttackNode::Execute()
{
	//std::cout << "Attacking the target." << std::endl;
	_Enemyobj->Attack();
	SelectorSuccess = true;
	return true;
}

bool TXT_AI::BehaviorTree::BlockNode::Execute()
{
	//std::cout << "Blocking" << std::endl;
	IsAttackBlocked = true;
	SelectorSuccess = true;
	return true;
}

bool TXT_AI::BehaviorTree::MagicSkillBlock::Execute()
{
	if (bSkillType_node == 0)
	{
		//std::cout << "�Ϲ� ��ų ��� �ߵ�" << std::endl;
		LogR_node->initiate_LogisticRegression();
		IsSkillBlocked = true;
		SelectorSuccess = true;
		return true;
	}
	else
	{
		//std::cout << "������ ��ų ��� �ߵ�" << std::endl;
		SoftR_node->Initiate_SoftmaxRegression();
		IsSkillBlocked = true;
		SelectorSuccess = true;
		return true;
	}
}

bool TXT_AI::BehaviorTree::IsMagicSkillUsed::Check()
{
	if(bSoftLearned == true && bSkillType_node == true)
	{
		if (bSkillUsed_node)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool TXT_AI::BehaviorTree::SkillBlockprob::Check()
{
	auto prob = dist(mt);

	if (prob >= 30)
	{
		//��ų ���
		return true;
	}
	else
	{
		SelectorSuccess = false;
		return false;
	}
}

bool TXT_AI::BehaviorTree::IsSkillUsed::Check()
{
	if (bLogiLearned == true && bSkillType_node == false)
	{
		if (bSkillUsed_node)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool TXT_AI::BehaviorTree::SkillBlock::Execute()
{
	if (bSkillType_node == 0)
	{
		//std::cout << "�Ϲ� ��ų ��� �ߵ�" << std::endl;
		LogR_node->initiate_LogisticRegression();
		IsSkillBlocked = true;
		SelectorSuccess = true;
		return true;
	}
	else
	{
		//std::cout << "������ ��ų ��� �ߵ�" << std::endl;
		SoftR_node->Initiate_SoftmaxRegression();
		IsSkillBlocked = true;
		SelectorSuccess = true;
		return true;
	}
}