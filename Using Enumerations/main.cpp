#include <iostream>
enum PLAYER_RANK
{
	PR_IRON,
	PR_BRONZE,
	PR_SILVER,
	PR_GOLD,
	PR_PLATINUM,
	PR_DIAMOND
};
enum MEMBERSHIP_TIER
{
	MT_GOLD,
	MT_SILVER,
	MT_FREE,
	MT_BANNED
};
void DisplaySizeChecks();
void PrintMembership(MEMBERSHIP_TIER membershipTier);
MEMBERSHIP_TIER UpgradeMembershipOneTier(MEMBERSHIP_TIER current);
void PrintPlayerRank(PLAYER_RANK playerRank);
void PromotePlayer(PLAYER_RANK& playerRank);
void DemotePlayer(PLAYER_RANK& playerRank);
int main()
{
	MEMBERSHIP_TIER exampleMembership = MT_FREE;
	PLAYER_RANK examplePlayer = PR_IRON;
	PrintMembership(exampleMembership);
	exampleMembership = UpgradeMembershipOneTier(exampleMembership);
	PrintMembership(exampleMembership);
	PrintPlayerRank(examplePlayer);
	PromotePlayer(examplePlayer);
	PrintPlayerRank(examplePlayer);
	PromotePlayer(examplePlayer);
	PrintPlayerRank(examplePlayer);
	PromotePlayer(examplePlayer);
	PrintPlayerRank(examplePlayer);
	DemotePlayer(examplePlayer);
	PrintPlayerRank(examplePlayer);
	DemotePlayer(examplePlayer);
	PrintPlayerRank(examplePlayer);
	PromotePlayer(examplePlayer);
	PrintPlayerRank(examplePlayer);
	DemotePlayer(examplePlayer);
	PrintPlayerRank(examplePlayer);
	DisplaySizeChecks();
	return 0;
}

void DisplaySizeChecks()
{
	std::cout << "sizeof(PLAYER_RANK) is " << sizeof(PLAYER_RANK);
	std::cout << " bytes." << std::endl;
	std::cout << "sizeof(MEMBERSHIP_STATUS) is ";
	std::cout << sizeof(MEMBERSHIP_TIER) << " bytes." << std::endl;
}

void DisplaySizesChecks()
{
	std::cout << "sizeof(PLAYER_RANK) is " << sizeof(PLAYER_RANK);
	std::cout << " bytes." << std::endl;
	std::cout << "sizeof(MEMBERSHIP_STATUS) is ";
	std::cout << sizeof(MEMBERSHIP_TIER) << " bytes." << std::endl;
}

MEMBERSHIP_TIER UpgradeMembershipOneTier(MEMBERSHIP_TIER current)
{
	if (current > MT_GOLD)
	{
		current = static_cast<MEMBERSHIP_TIER>(current - 1);
	}
	return current;
}
void PrintMembership(MEMBERSHIP_TIER membershipTier)
{
	switch (membershipTier)
	{
	case MT_GOLD:
		std::cout << "Member is gold level!" << std::endl;
		break;
	case MT_SILVER:
		std::cout << "Member is silver level." << std::endl;
		break;
	case MT_FREE:
		std::cout << "Member is freemium." << std::endl;
		break;
	case MT_BANNED:
		std::cout << "Member is banned!" << std::endl;
		break;
	default:
		std::cout << "Unknown membership!" << std::endl;
		break;
	}
}

void PrintPlayerRank(PLAYER_RANK playerRank) {
	switch (playerRank)
	{
	case PR_IRON:
		std::cout << "Player is Iron!\n" << std::endl;
		break;
	case PR_BRONZE:
		std::cout << "Player is Bronze!\n" << std::endl;
		break;
	case PR_SILVER:
		std::cout << "Player is Silver!\n" << std::endl;
		break;
	case PR_GOLD:
		std::cout << "Player is Gold!\n" << std::endl;
		break;
	case PR_PLATINUM:
		std::cout << "Player is Platinum!\n" << std::endl;
		break;
	case PR_DIAMOND:
		std::cout << "Player is Diamond!\n" << std::endl;
		break;
	default:
		std::cout << "Unknown membership!\n" << std::endl;
		break;
	}
}

void DemotePlayer(PLAYER_RANK& playerRank) {
	switch (playerRank)
	{
	case PR_IRON:
		std::cout << "Already lowest!" << std::endl;
		break;
	case PR_BRONZE:
		playerRank = PR_IRON;
		break;
	case PR_SILVER:
		playerRank = PR_BRONZE;
		break;
	case PR_GOLD:
		playerRank = PR_SILVER;
		break;
	case PR_PLATINUM:
		playerRank = PR_GOLD;
		break;
	case PR_DIAMOND:
		playerRank = PR_PLATINUM;
		break;
	default:
		std::cout << "Unknown membership!" << std::endl;
		break;
	}
}
void PromotePlayer(PLAYER_RANK& playerRank) {
	switch (playerRank)
	{
	case PR_IRON:
		playerRank = PR_BRONZE;
		break;
	case PR_BRONZE:
		playerRank = PR_SILVER;
		break;
	case PR_SILVER:
		playerRank = PR_GOLD;
		break;
	case PR_GOLD:
		playerRank = PR_PLATINUM;
		break;
	case PR_PLATINUM:
		playerRank = PR_DIAMOND;
		break;
	case PR_DIAMOND:
		std::cout << "Already max!" << std::endl;
		break;
	default:
		std::cout << "Unknown membership!" << std::endl;
		break;
	}
}