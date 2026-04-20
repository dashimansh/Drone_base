#pragma once
#include "CoreMinimal.h"

struct FPIDController
{
    float Kp, Ki, Kd;
    float Integral;
    float PreviousError;

    FPIDController(float InKp = 1.f, float InKi = 0.f, float InKd = 0.f)
        : Kp(InKp), Ki(InKi), Kd(InKd),
        Integral(0.f), PreviousError(0.f) {}

    float Update(float Error, float DeltaTime)
    {
        Integral += Error * DeltaTime;
        float Deriv = (Error - PreviousError) / FMath::Max(DeltaTime, 0.0001f);
        PreviousError = Error;
        return Kp * Error + Ki * Integral + Kd * Deriv;
    }

    void Reset()
    {
        Integral = 0.f;
        PreviousError = 0.f;
    }
};