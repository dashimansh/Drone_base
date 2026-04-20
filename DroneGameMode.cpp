#include "DroneGameMode.h"
#include "DronePawn.h"
#include "DroneHUD.h"

ADroneGameMode::ADroneGameMode()
{
    DefaultPawnClass = ADronePawn::StaticClass();
    HUDClass = ADroneHUD::StaticClass();
}