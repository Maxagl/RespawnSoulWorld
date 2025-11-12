// Zhaobang Liu All Rights Reserved


#include "Controllers/FrontEndPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

void AFrontEndPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	TArray<AActor*> FoundCameras;
	UGameplayStatics::GetAllActorsOfClassWithTag(this, ACameraActor::StaticClass(), FName("Default"), FoundCameras);

	if (!FoundCameras.IsEmpty())
	{
		SetViewTarget(FoundCameras[0]);
	}
}
