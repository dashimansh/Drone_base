#include "DroneHUD.h"
#include "DronePawn.h"
#include "Engine/Canvas.h"
#include "Engine/Engine.h"
#include "GameFramework/PlayerController.h"
#include "CanvasItem.h"

void ADroneHUD::DrawHUD()
{
    Super::DrawHUD();

    APlayerController* PC = GetOwningPlayerController();
    if (!PC) return;

    ADronePawn* Drone = Cast<ADronePawn>(PC->GetPawn());
    if (!Drone) return;

    float   Battery = Drone->GetBattery();
    float   Speed = Drone->GetSpeed();
    float   Altitude = Drone->GetAltitude();
    FVector Wind = Drone->GetWindDirection();
    bool    Crashed = Drone->IsCrashed();

    // ── Battery Bar ──────────────────────────────────────────
    DrawRect(FLinearColor::Black, 15, 15, 254, 34);

    FLinearColor BarColor;
    if (Battery > 60.f) BarColor = FLinearColor::Green;
    else if (Battery > 30.f) BarColor = FLinearColor::Yellow;
    else                     BarColor = FLinearColor::Red;

    float BarWidth = (Battery / 100.f) * 250.f;
    DrawRect(BarColor, 17, 17, BarWidth, 30);

    // ── Colors ───────────────────────────────────────────────
    FLinearColor White = FLinearColor::White;
    FLinearColor Red = FLinearColor::Red;
    FLinearColor Cyan = FLinearColor(0.f, 1.f, 1.f, 1.f);
    FLinearColor Gray = FLinearColor(0.5f, 0.5f, 0.5f, 1.f);

    // ── Text ─────────────────────────────────────────────────
    DrawText(
        FString::Printf(TEXT("Battery: %.0f%%"), Battery),
        20, 55, Battery > 30.f ? White : Red);

    DrawText(
        FString::Printf(TEXT("Speed: %.0f cm/s"), Speed),
        20, 80, White);

    DrawText(
        FString::Printf(TEXT("Altitude: %.0f cm"), Altitude),
        20, 105, White);

    DrawText(
        FString::Printf(TEXT("Wind: X=%.0f Y=%.0f"), Wind.X, Wind.Y),
        20, 130, Cyan);

    // ── Controls ← Updated C instead of V ───────────────────
    DrawText(
        TEXT("C=FPV | R=Recharge | T=Reset"),
        20, 155, Gray);

    // ── Crash Warning ────────────────────────────────────────
    if (Crashed && Canvas)
    {
        DrawText(
            TEXT("DRONE CRASHED! Press T to Reset!"),
            Canvas->SizeX / 2.f - 200.f,
            Canvas->SizeY / 2.f,
            Red);
    }

    // ── Low Battery Warning ──────────────────────────────────
    if (Battery < 20.f && !Crashed && Canvas)
    {
        DrawText(
            TEXT("LOW BATTERY! Press R!"),
            Canvas->SizeX / 2.f - 150.f,
            60.f, Red);
    }
}

void ADroneHUD::DrawText(
    const FString& Text, float X, float Y, FLinearColor Color)
{
    if (!Canvas || !GEngine) return;

    FCanvasTextItem TextItem(
        FVector2D(X, Y),
        FText::FromString(Text),
        GEngine->GetMediumFont(),
        Color
    );
    TextItem.Scale = FVector2D(1.5f, 1.5f);
    Canvas->DrawItem(TextItem);
}