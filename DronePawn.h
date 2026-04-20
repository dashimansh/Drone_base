#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PIDController.h"
#include "DronePawn.generated.h"

UCLASS()
class MACDONALD_API ADronePawn : public APawn
{
    GENERATED_BODY()

public:
    ADronePawn();

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

    // ── Components ──────────────────────────────────────────
    UPROPERTY(VisibleAnywhere) UStaticMeshComponent* DroneMesh;
    UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Rotor_FL;
    UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Rotor_FR;
    UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Rotor_BL;
    UPROPERTY(VisibleAnywhere) UStaticMeshComponent* Rotor_BR;
    UPROPERTY(VisibleAnywhere) class USpringArmComponent* SpringArm;
    UPROPERTY(VisibleAnywhere) class UCameraComponent* Camera;
    UPROPERTY(VisibleAnywhere) class UCameraComponent* FPVCamera;

    // ── Physics ─────────────────────────────────────────────
    UPROPERTY(EditAnywhere, Category = "Drone|Physics")
        float Mass = 1.0f;

    UPROPERTY(EditAnywhere, Category = "Drone|Physics")
        float MaxThrust = 2000.f;

    UPROPERTY(EditAnywhere, Category = "Drone|Physics")
        float MaxTiltAngle = 35.f;

    // ── PID Gains ───────────────────────────────────────────
    UPROPERTY(EditAnywhere, Category = "Drone|PID")
        float Altitude_Kp = 2.f, Altitude_Ki = 0.0f, Altitude_Kd = 0.5f;

    UPROPERTY(EditAnywhere, Category = "Drone|PID")
        float Pitch_Kp = 6.f, Pitch_Ki = 0.05f, Pitch_Kd = 3.f;

    UPROPERTY(EditAnywhere, Category = "Drone|PID")
        float Roll_Kp = 6.f, Roll_Ki = 0.05f, Roll_Kd = 3.f;

    // ── Rotors ──────────────────────────────────────────────
    UPROPERTY(EditAnywhere, Category = "Drone|Rotors")
        float RotorSpinSpeed = 2000.f;

    // ── Battery ─────────────────────────────────────────────
    UPROPERTY(EditAnywhere, Category = "Drone|Battery")
        float MaxBattery = 100.f;

    UPROPERTY(EditAnywhere, Category = "Drone|Battery")
        float BatteryDrainRate = 5.f;

    UPROPERTY(EditAnywhere, Category = "Drone|Battery")
        float BatteryRechargeRate = 20.f;

    // ── Wind ────────────────────────────────────────────────
    UPROPERTY(EditAnywhere, Category = "Drone|Wind")
        float WindStrength = 50.f;

    UPROPERTY(EditAnywhere, Category = "Drone|Wind")
        float WindChangeInterval = 3.f;

public:
    // ── HUD Getters ─────────────────────────────────────────
    UFUNCTION(BlueprintCallable) float   GetSpeed()         const;
    UFUNCTION(BlueprintCallable) float   GetAltitude()      const;
    UFUNCTION(BlueprintCallable) float   GetBattery()       const;
    UFUNCTION(BlueprintCallable) bool    IsCrashed()        const;
    UFUNCTION(BlueprintCallable) FVector GetWindDirection() const;

private:
    // PIDs
    FPIDController PID_Altitude;
    FPIDController PID_Pitch;
    FPIDController PID_Roll;

    // Input
    float InputThrottle = 0.f;
    float InputPitch = 0.f;
    float InputRoll = 0.f;
    float InputYaw = 0.f;

    // Physics state
    FVector Velocity = FVector::ZeroVector;
    FVector PreviousVelocity = FVector::ZeroVector;
    float   CurrentYaw = 0.f;
    float   RotorAngle = 0.f;

    // Battery
    float CurrentBattery = 100.f;
    bool  bIsDead = false;

    // Wind
    FVector CurrentWind = FVector::ZeroVector;
    float   WindTimer = 0.f;

    // Crash
    bool bCrashed = false;

    // FPV
    bool bIsFPV = false;

    // Input callbacks
    void OnThrottleUp(float Val);
    void OnPitch(float Val);
    void OnRoll(float Val);
    void OnYaw(float Val);

    // Functions
    void ApplyDronePhysics(float DeltaTime);
    void SpinRotors(float DeltaTime);
    void UpdateWind(float DeltaTime);
    void CheckCrash();
    void Recharge();
    void ResetDrone();
    void ToggleFPV();
};