/*
	by unitx 12.22.2018 (3.1.2019 - lastUpdate)
*/

#include "Engine.h"
#include "EnfusionEngine.h"

int main()
{
	EnfusionProcess::AutoGameSelection(Analysis::Deep);

	static bool bRemoveGrass{ false };

	while (true) 
	{
		/*
		printf("Server: %s \n", EnfusionEngine::GetNetworkClientServerName().c_str());
		printf("Players Online: %d \n", EnfusionEngine::GetCountOfPlayers()); */

		
		for (uint64_t Entity : EnfusionEngine::GetAllEntityes()) // all players
		{
			Vector3 worldPosition = EnfusionEngine::GetCoordinate(Entity);
			Vector3 screenPosition = EnfusionEngine::WorldToScreen(worldPosition);

			printf("PlayerName: %s                \n", EnfusionEngine::GetPlayerName(Entity).c_str());
			printf("Type: %s                      \n", EnfusionEngine::GetTypeName(Entity).c_str());
			printf("Model: %s                     \n", EnfusionEngine::GetModelName(Entity).c_str());
			printf("Item in Hands: %s             \n", EnfusionEngine::GetItemInHands(Entity).c_str());
			printf("Distance: %.0fm               \n", EnfusionEngine::GetDistanceToMe(worldPosition));
			printf("Position: %.1f : %.1f : %.1f  \n", worldPosition.x, worldPosition.y, worldPosition.z);
			printf("SceenPosition: %.1f : %.1f    \n", screenPosition.x, screenPosition.y);

			float centerX = Render.Width / 2.0f;
			float centerY = Render.Height / 2.0f;

			if (GetAsyncKeyState(VK_LMENU))
			{
				float radius = 30.0f;
				if (screenPosition.x - centerX < radius && centerX - screenPosition.x < radius &&
					centerY - screenPosition.y < radius && screenPosition.y - centerY < radius)
				{
					EnfusionEngine::KillBySilentAim(Entity);
				}
			}
		}

		//Camera control

		if (GetAsyncKeyState(VK_UP) < 0) { 
			EnfusionEngine::MovCameraForward();
		}

		if (GetAsyncKeyState(VK_DOWN) < 0) { 
			EnfusionEngine::MovCameraBackward();
		}

		if (GetAsyncKeyState(VK_LEFT) < 0) { 
			EnfusionEngine::MovCameraLeft();
		}

		if (GetAsyncKeyState(VK_RIGHT) < 0) { 
			EnfusionEngine::MovCameraRight();
		}

		if (GetAsyncKeyState(VK_PRIOR) < 0) { 
			EnfusionEngine::MovCameraUp();
		}

		if (GetAsyncKeyState(VK_NEXT) < 0) { 
			EnfusionEngine::MovCameraDown();
		}

		if (GetAsyncKeyState(VK_F1) & 1) bRemoveGrass = !bRemoveGrass;

		if (bRemoveGrass)
			EnfusionEngine::SetTerrainGrid(0.f); // remove grass
		else
			EnfusionEngine::SetTerrainGrid(10.f); // add grass back
	}

	return 0;
}
