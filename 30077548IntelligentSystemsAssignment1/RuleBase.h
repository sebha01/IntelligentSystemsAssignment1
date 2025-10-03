#pragma once
#include "GlobalHeader.h"
#include "Rule.h"

class RuleBase {
	private:
		std::vector<Rule> rules = 
		{
			//Few customers so leave
			{
				{{"customers", "few"}},
				LEAVE
			}, 
			//Some customers so wait
			{
				{{"customers", "some"}},
				WAIT
			},
			//Full of customers, waiting time greater than 60 mins so leave
			{
				{{"customers", "full"}, {"waitTime", ">60"}},
				LEAVE
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant yes, so leave
			{
				{{"customers", "full"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "yes"}},
				LEAVE
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation no, bar no, so leave
			{
				{{"customers", "full"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "no"}, {"reservation", "no"}, { "bar", "no" }},
				LEAVE
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation no, bar yes, so wait
			{
				{{"customers", "full"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "no"}, {"reservation", "no"}, {"bar", "yes"}},
				WAIT
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation yes, popular day no, so leave
			{
				{{"customers", "full"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "no"}, {"reservation", "yes"}, {"popularDay", "no"}},
				LEAVE
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation yes, popular day yes, so wait
			{
				{{"customers", "full"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "no"}, {"reservation", "yes"}, {"popularDay", "yes"}},
				WAIT
			},
			//Full of customers, waiting time 10-30 mins, hungry no, so wait
			{
				{{"customers", "full"}, {"waitTime", "10-30"}, {"hungry", "no"}},
				WAIT
			},
			//Full of customers, waiting time 10-30 mins, hungry yes, alternative no, so wait
			{
				{{"customers", "full"}, {"waitTime", "10-30"}, {"hungry", "yes"}, {"alternativeRestaurant", "no"}},
				WAIT
			},
			//Full of customers, waiting time 10-30 mins, hungry yes, alternative yes, raining yes, so wait
			{
				{{"customers", "full"}, {"waitTime", "10-30"}, {"hungry", "yes"}, {"alternativeRestaurant", "yes"}, {"raining", "yes"}},
				WAIT
			},
			//Full of customers, waiting time 10-30 mins, hungry yes, alternative yes, raining no, so leave
			{
				{{"customers", "full"}, {"waitTime", "10-30"}, {"hungry", "yes"}, {"alternativeRestaurant", "yes"}, {"raining", "no"}},
				LEAVE
			},
			//Full of customers, waiting time less than 10 mins so wait
			{
				{{"customers", "full"}, {"waitTime", "<10"}},
				WAIT
			}
		};
	public:
		std::vector<Rule> getRules();
		void removeNonNeededRule(int index);
};

std::vector<Rule> RuleBase::getRules()
{
	return rules;
}

void RuleBase::removeNonNeededRule(int index)
{
	rules.erase(rules.begin() + index);
}