#pragma once
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include "Enemy.h"

using namespace TXT_Enemy;

namespace TXT_AI
{
	/*
	*Variable for SoftmaxRegression and LogisticRegression
	*/
	using dataType = double;
	constexpr double learning_rate = 1e-2;
	constexpr int num_classes = 4;
	constexpr int num_features = 1;

	class SoftmaxRegression;
	class LogisticRegression;

	/*BehaviorTree class*/
	class BehaviorTree
	{
	public:
		BehaviorTree();
	private:
		//BehaviorTree(BehaviorTree& _BTree_Param);
		//BehaviorTree(BehaviorTree&& _BTree_Param);
		//void operator=(BehaviorTree& _BTree_Param);
		//void operator=(BehaviorTree&& _BTree_Param);

		//전방 선언
		class Decorator;
		class SequenceNode;
		class SelectorNode;
		class RootNode;
		class ActionNode;

	protected:
		/*private variable section*/
		RootNode* root;
		Enemy* Enemyobj;
		bool bSkillUsed;
		bool bSkillType;
		static bool bSoftLearned;
		static bool bLogiLearned;
		LogisticRegression* LogR;
		SoftmaxRegression* SoftR;
		static bool IsSkillBlocked;
		static bool IsAttackBlocked;

		/*interface Section*/

		//노드 타입 열거형
		enum class Node_Type
		{
			NT_Selector,
			NT_Sequence,
			NT_Action,
			NT_Decorator,

			NT_Root,
			NT_Default
		};

		//노드 Interface 클래스
		class node
		{
		public:
			Node_Type NType;
			std::vector<node*> nodes;
			std::vector<Decorator*> Conditions;
			Enemy* _Enemyobj;
			static bool SelectorSuccess;
			bool bSkillType_node;
			bool bSkillUsed_node;
			SoftmaxRegression* SoftR_node;
			LogisticRegression* LogR_node;
			//TODO:sequence node의 자식들의 성공 여부 변수
			//int SequenceSuccess;

			node();
			~node();
			Node_Type Get_NType() const;
			virtual bool Execute() = 0;
			virtual void AddChild(node* child) = 0;
			virtual bool checking_conditions() = 0;
			virtual std::vector<node*>& GetSubTree() = 0;
			virtual std::vector<Decorator*>& GetConditions() = 0;
			virtual void AddDecorator(Decorator*) = 0;
			virtual bool Check() = 0;
			//virtual bool AbortCheck()
			//{
			//	//default
			//	return true;
			//}
			void SetEnemy(Enemy* _Enemy)
			{
				_Enemyobj = _Enemy;
			}
			void SetSkillType(bool _SkillType)
			{
				bSkillType_node = _SkillType;
			}
			void SetSkillUsed(bool _SkillUsed)
			{
				bSkillUsed_node = _SkillUsed;
			}
			void SetSoftR(SoftmaxRegression* _SoftR)
			{
				SoftR_node = _SoftR;
			}
			void SetLogR(LogisticRegression* _LogR)
			{
				LogR_node = _LogR;
			}
		};

		// 행동 노드 클래스
		class ActionNode :public node
		{
		public:
			bool Execute() override { return true; }
			void AddChild(node* child) override {}
			bool checking_conditions() override { return true; }
			std::vector<node*>& GetSubTree() override { return nodes; }
			std::vector<Decorator*>& GetConditions() override { return Conditions; }
			void AddDecorator(Decorator* Condition) override {}
			bool Check() override { return true; }
			ActionNode();
		};

		// 조건 노드 클래스
		class Decorator : public node
		{
		public:
			bool Execute() override { return true; }
			void AddChild(node* child) override {}
			bool checking_conditions() override { return true; }
			std::vector<node*>& GetSubTree() override { return nodes; }
			std::vector<Decorator*>& GetConditions() override { return Conditions; }
			void AddDecorator(Decorator* Condition) override {}
			bool Check() override { return true; }
			Decorator();
		};

		//셀렉터 노드 클래스
		class SelectorNode : public node
		{
		public:
			SelectorNode();
			bool Execute() override;
			std::vector<node*>& GetSubTree() override
			{
				return nodes;
			}
			void AddChild(node* child) override
			{
				nodes.push_back(child);
			}
			bool checking_conditions() override { return true; }
			std::vector<Decorator*>& GetConditions() override { return Conditions; }
			void AddDecorator(Decorator* Condition) override {}
			bool Check() override { return true; }
			//bool AbortCheck() override;
		};

		//시퀀스 노드 클래스
		class SequenceNode : public node
		{
		public:
			SequenceNode();
			bool Execute() override;
			bool checking_conditions() override;
			std::vector<node*>& GetSubTree() override
			{
				return nodes;
			}
			std::vector<Decorator*>& GetConditions() override
			{
				return Conditions;
			}
			void AddDecorator(Decorator* Condition) override
			{
				Conditions.push_back(Condition);
			}
			void AddChild(node* child) override
			{
				nodes.push_back(child);
			}
			bool Check() override { return true; }
		};

		//루트 노드 클래스
		class RootNode :public node
		{
		public:
			RootNode();
			bool Execute() override;
			void AddChild(node* child) override
			{
				nodes.push_back(child);
			}
			std::vector<node*>& GetSubTree() override
			{
				return nodes;
			}
			bool checking_conditions() override { return true; }
			std::vector<Decorator*>& GetConditions() override { return Conditions; }
			void AddDecorator(Decorator* Condition) override {}
			bool Check() override { return true; }
		};


		/*
		*Inheritance class Section
		*/
	public:
		class MoveNode : public ActionNode
		{
		public:
			bool Execute() override
			{
				std::cout << "Moving to a location." << std::endl;
				return true;
			}
		};

		class AttackNode : public ActionNode
		{
		public:
			bool Execute() override;
		};

		class BlockNode :public ActionNode
		{
		public:
			bool Execute() override;
		};

		class MagicSkillBlock :public ActionNode
		{
		public:
			bool Execute() override;
		};

		class SkillBlock :public ActionNode
		{
		public:
			bool Execute() override;
		};

		class HealthLowNode : public Decorator
		{
		public:
			bool Check() override;
		};

		class AttackorBlock :public Decorator
		{
		public:
			bool Check() override;
		};

		class IsMagicSkillUsed :public Decorator
		{
		public:
			bool Check() override;
		};

		class IsSkillUsed :public Decorator
		{
		public:
			bool Check() override;
		};

		class SkillBlockprob :public Decorator
		{
		public:
			bool Check() override;
		};

		class AttackCharacter : public SequenceNode
		{
		public:
		};

		class BlockCharacter :public SequenceNode
		{
		public:
		};

		class BlockMagicSkill :public SequenceNode
		{
		public:
		};
		class BlockSkill :public SequenceNode
		{
		public:
		};


		class Selector_1 :public SelectorNode
		{
		public:
		};
		Decorator* GetSkillDecorator() const
		{
			return root->GetSubTree()[0]->GetSubTree()[0]->GetConditions()[0];
		}
	public:
		~BehaviorTree();
		bool Initiate_BTree();
		void Init_BTree(Enemy* _Enemy);
		/*
		*void Init_BTree_Boss();
		*void Init_BTree_Ghoul();
		* ...
		*/
		node* GetRoot()
		{
			return root;
		}
		void SetEnemyobj(Enemy* _Enemyobj)
		{
			Enemyobj = _Enemyobj;
		}
		void SetSkillType(bool _SkillType)
		{
			bSkillType = _SkillType;
		}
		void SetSkillUsed(bool _SkillUsed)
		{
			bSkillUsed = _SkillUsed;
		}
		void SetSoftLearned(bool _bLearned)
		{
			bSoftLearned = _bLearned;
		}
		void SetLogiLearned(bool _bLearned)
		{
			bLogiLearned = _bLearned;
		}
		LogisticRegression* GetLogR()
		{
			return LogR;
		}
		SoftmaxRegression* GetSoftR()
		{
			return SoftR;
		}
		static bool GetSKillBlocked()
		{
			return IsSkillBlocked;
		}
		static bool GetAttackBlocked()
		{
			return IsAttackBlocked;
		}
		
	};
	class SoftmaxRegression
	{
	private:
		std::vector<dataType> X;
		std::vector<int> Y;
		int ipredict;
	public:
		SoftmaxRegression();
		std::vector<dataType> softmax(const std::vector<dataType>& z);
		dataType crossEntropyLoss(const std::vector<dataType>& predicted_probs, int true_label);
		void SoftmaxRegression_training(std::vector<dataType>& X, std::vector<int>& Y, std::vector<std::vector<dataType>>& weights, int epochs, double lr);
		void Initiate_SoftmaxRegression();
		void init_vector();
		std::vector<int>& GetArray()
		{
			return Y;
		}
		int Getpredict() const
		{
			return ipredict;
		}
	};

	class LogisticRegression
	{
	private:
		std::vector<dataType> X;
		std::vector<dataType> Y;
		int ipredict;
	public:
		LogisticRegression();
		double sigmoid(double z);
		double GradientDescent(std::vector<dataType>& X, std::vector<dataType>& Y, double& W, double& b, double lr);
		void LogisticRegression_training(std::vector<dataType>& X, std::vector<dataType>& Y, double& W, double& b, int epochs, double lr);
		double predict(double& W, double& b, dataType X);
		void init_vector();
		void initiate_LogisticRegression();
		std::vector<dataType>& GetArray()
		{
			return Y;
		}
		int Getpredict() const
		{
			return ipredict;
		}
	};
}