#pragma once
#include "GlobalHeader.h"
#include "Rule.h"

class RuleBase {
	private:
		std::vector<Rule> rules = 
		{
			//Few customers so leave
			{
				{{"customers", "A few customers"}},
				LEAVE
			}, 
			//Some customers so wait
			{
				{{"customers", "Some customers"}},
				WAIT
			},
			//Full of customers, waiting time greater than 60 mins so leave
			{
				{{"customers", "Full of customers"}, {"wait time", "More than 60 minutes"}},
				LEAVE
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant yes, so leave
			{
				{{"customers", "Full of customers"}, {"wait time", "Between 31 and 60 minutes"}, {"Alternative restaurant", "Yes"}},
				LEAVE
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation no, bar no, so leave
			{
				{{"customers", "Full of customers"}, {"wait time", "Between 31 and 60 minutes"}, {"Alternative restaurant", "No"}, {"Reservation", "No"}, { "Bar", "No" }},
				LEAVE
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation no, bar yes, so wait
			{
				{{"customers", "Full of customers"}, {"wait time", "Between 31 and 60 minutes"}, {"Alternative restaurant", "No"}, {"Reservation", "No"}, {"Bar", "Yes"}},
				WAIT
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation yes, popular day no, so leave
			{
				{{"customers", "Full of customers"}, {"wait time", "Between 31 and 60 minutes"}, {"Alternative restaurant", "No"}, {"Reservation", "Yes"}, {"Popular day", "No"}},
				LEAVE
			},
			//Full of customers, waiting time 31-60 mins, alternative restaurant no, reservation yes, popular day yes, so wait
			{
				{{"customers", "Full of customers"}, {"wait time", "Between 31 and 60 minutes"}, {"Alternative restaurant", "No"}, {"Reservation", "Yes"}, {"Popular day", "Yes"}},
				WAIT
			},
			//Full of customers, waiting time 10-30 mins, hungry no, so wait
			{
				{{"customers", "Full of customers"}, {"wait time", "Between 10 and 30 minutes"}, {"Hungry", "No"}},
				WAIT
			},
			//Full of customers, waiting time 10-30 mins, hungry yes, alternative no, so wait
			{
				{{"customers", "Full of customers"}, {"wait time", "Between 10 and 30 minutes"}, {"Hungry", "Yes"}, {"Alternative restaurant", "No"}},
				WAIT
			},
			//Full of customers, waiting time 10-30 mins, hungry yes, alternative yes, raining yes, so wait
			{
				{{"customers", "Full of customers"}, {"wait time", "Between 10 and 30 minutes"}, {"Hungry", "Yes"}, {"Alternative restaurant", "Yes"}, {"Raining", "Yes"}},
				WAIT
			},
			//Full of customers, waiting time 10-30 mins, hungry yes, alternative yes, raining no, so leave
			{
				{{"customers", "Full of customers"}, {"wait time", "Between 10 and 30 minutes"}, {"Hungry", "Yes"}, {"Alternative restaurant", "Yes"}, {"Raining", "No"}},
				LEAVE
			},
			//Full of customers, waiting time less than 10 mins so wait
			{
				{{"customers", "Full of customers"}, {"wait time", "Less than 10 minutes"}},
				WAIT
			}
		};
	public:
		std::vector<Rule>& getRules();
};

std::vector<Rule>& RuleBase::getRules()
{
	return rules;
}
