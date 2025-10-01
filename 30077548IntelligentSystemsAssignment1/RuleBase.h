#pragma once
#include "GlobalHeader.h"
#include "Rule.h"

class RuleBase {
	private:
		const std::vector<Rule>& rules = 
		{
			//Few customers so leave
			{
				{{"customers", "few"}},
				{"decision", "leave"}
			}, 
			//Some customers so wait
			{
				{{"customers", "some"}},
				{"decision", "wait"}
			},
			//Full of customers, waiting time greater than 60 mins so leave
			{
				{{"customers", "full"}, {"waitTime", ">60"}},
				{"decision", "leave"}
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant yes, so leave
			{
				{{"customers", "full"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "yes"}},
				{"decision", "leave"}
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation no, bar no, so leave
			{
				{{"customers", "full"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "no"}, {"reservation", "no"}, { "bar", "no" }},
				{"decision", "leave"}
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation no, bar yes, so wait
			{
				{{"customers", "full"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "no"}, {"reservation", "no"}, {"bar", "yes"}},
				{"decision", "wait"}
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation yes, popular day no, so leave
			{
				{{"customers", "full"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "no"}, {"reservation", "yes"}, {"popularDay", "no"}},
				{"decision", "leave"}
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation yes, popular day yes, so wait
			{
				{{"customers", "full"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "no"}, {"reservation", "yes"}, {"popularDay", "yes"}},
				{"decision", "wait"}
			},
			//Full of customers, waiting time 10-30 mins, hungry no, so wait
			{
				{{"customers", "full"}, {"waitTime", "10-30"}, {"hungry", "no"}},
				{"decision", "wait"}
			},
			//Full of customers, waiting time 10-30 mins, hungry yes, alternative no, so wait
			{
				{{"customers", "full"}, {"waitTime", "10-30"}, {"hungry", "yes"}, {"alternativeRestaurant", "no"}},
				{"decision", "wait"}
			},
			//Full of customers, waiting time 10-30 mins, hungry yes, alternative yes, raining yes, so wait
			{
				{{"customers", "full"}, {"waitTime", "10-30"}, {"hungry", "yes"}, {"alternativeRestaurant", "yes"}, {"raining", "yes"}},
				{"decision", "wait"}
			},
			//Full of customers, waiting time 10-30 mins, hungry yes, alternative yes, raining no, so leave
			{
				{{"customers", "full"}, {"waitTime", "10-30"}, {"hungry", "yes"}, {"alternativeRestaurant", "yes"}, {"raining", "no"}},
				{"decision", "leave"}
			},
			//Full of customers, waiting time less than 10 mins so wait
			{
				{{"customers", "full"}, {"waitTime", "<10"}},
				{"decision", "wait"}
			}
		};
	public:
		std::vector<Rule> getRules();
};

std::vector<Rule> RuleBase::getRules()
{
	return rules;
}