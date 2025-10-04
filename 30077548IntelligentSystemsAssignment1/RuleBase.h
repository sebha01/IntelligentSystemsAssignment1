#pragma once
#include "GlobalHeader.h"
#include "Rule.h"

class RuleBase {
	private:
		std::vector<Rule> rules = 
		{
			//Few customers so leave
			{
				{{"customers", "A few"}},
				LEAVE
			}, 
			//Some customers so wait
			{
				{{"customers", "Some"}},
				WAIT
			},
			//Full of customers, waiting time greater than 60 mins so leave
			{
				{{"customers", "Full of customers"}, {"waitTime", ">60"}},
				LEAVE
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant yes, so leave
			{
				{{"customers", "Full of customers"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "Yes"}},
				LEAVE
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation no, bar no, so leave
			{
				{{"customers", "Full of customers"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "No"}, {"reservation", "No"}, { "bar", "No" }},
				LEAVE
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation no, bar yes, so wait
			{
				{{"customers", "Full of customers"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "No"}, {"reservation", "No"}, {"bar", "Yes"}},
				WAIT
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation yes, popular day no, so leave
			{
				{{"customers", "Full of customers"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "No"}, {"reservation", "Yes"}, {"popularDay", "No"}},
				LEAVE
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation yes, popular day yes, so wait
			{
				{{"customers", "Full of customers"}, {"waitTime", "31-60"}, {"alternativeRestaurant", "No"}, {"reservation", "Yes"}, {"popularDay", "Yes"}},
				WAIT
			},
			//Full of customers, waiting time 10-30 mins, hungry no, so wait
			{
				{{"customers", "Full of customers"}, {"waitTime", "10-30"}, {"hungry", "No"}},
				WAIT
			},
			//Full of customers, waiting time 10-30 mins, hungry yes, alternative no, so wait
			{
				{{"customers", "Full of customers"}, {"waitTime", "10-30"}, {"hungry", "Yes"}, {"alternativeRestaurant", "No"}},
				WAIT
			},
			//Full of customers, waiting time 10-30 mins, hungry yes, alternative yes, raining yes, so wait
			{
				{{"customers", "Full of customers"}, {"waitTime", "10-30"}, {"hungry", "Yes"}, {"alternativeRestaurant", "Yes"}, {"raining", "Yes"}},
				WAIT
			},
			//Full of customers, waiting time 10-30 mins, hungry yes, alternative yes, raining no, so leave
			{
				{{"customers", "Full of customers"}, {"waitTime", "10-30"}, {"hungry", "Yes"}, {"alternativeRestaurant", "Yes"}, {"raining", "No"}},
				LEAVE
			},
			//Full of customers, waiting time less than 10 mins so wait
			{
				{{"customers", "Full of customers"}, {"waitTime", "<10"}},
				WAIT
			}
		};
	public:
		std::vector<Rule> getRules();
};

std::vector<Rule> RuleBase::getRules()
{
	return rules;
}
