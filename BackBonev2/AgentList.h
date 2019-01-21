#pragma once

#include "Agent.h"

class AgentList
{
	Agent *root;
	Agent *conductor;
public:
	AgentList();
	~AgentList();

	Agent *GetNextAgent();
	Agent *ResetConductor();

	void AppendAgent(Agent *agent);
	void RemoveAgent(Agent *agent);
};

