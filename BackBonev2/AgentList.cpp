#include "stdafx.h"
#include "AgentList.h"


AgentList::AgentList()
{
	root = NULL;
	conductor = NULL;
}

AgentList::~AgentList()
{
}

Agent * AgentList::GetNextAgent()
{
	return conductor = conductor->nextAgent;
}

Agent * AgentList::ResetConductor()
{
	conductor = root;
	return conductor;
}

void AgentList::AppendAgent(Agent * agent)
{
	Agent *cond = root;
	if (cond != NULL)
	{
		while (cond->nextAgent != NULL)
			cond = cond->nextAgent;
		cond->nextAgent = agent;
	}
	else
	{
		root = agent;
	}
}

void AgentList::RemoveAgent(Agent * agent)
{
	if (agent != NULL && root != NULL)
	{
		if (root == agent)
		{
			root = root->nextAgent;
			return;
		}

		Agent *cond = root;
		Agent *toDelete;
		while (cond->nextAgent != agent)
			cond = cond->nextAgent;
		toDelete = cond->nextAgent;
		cond->nextAgent = cond->nextAgent->nextAgent;
		delete toDelete;
	}
}
