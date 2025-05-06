ImVec2 CalculateAimOffset(const FVector2D& target2D, const ImVec2& screenCenter, int aimSpeed, float screenWidth, float screenHeight) {
	float targetX = 0.0f;
	float targetY = 0.0f;

	if (target2D.x != 0) {
		targetX = (target2D.x > screenCenter.x) ? -(screenCenter.x - target2D.x) / aimSpeed : (target2D.x - screenCenter.x) / aimSpeed;
		if ((target2D.x > screenCenter.x && targetX + screenCenter.x > screenWidth) ||
			(target2D.x < screenCenter.x && targetX + screenCenter.x < 0)) {
			targetX = 0.0f;
		}
	}

	if (target2D.y != 0) {
		targetY = (target2D.y > screenCenter.y) ? -(screenCenter.y - target2D.y) / aimSpeed : (target2D.y - screenCenter.y) / aimSpeed;
		if ((target2D.y > screenCenter.y && targetY + screenCenter.y > screenHeight) ||
			(target2D.y < screenCenter.y && targetY + screenCenter.y < 0)) {
			targetY = 0.0f;
		}
	}

	return ImVec2(targetX, targetY);
}

void aimbotPlayer( uintptr_t pawnprivate ) {
	
	uintptr_t targetMesh = request->read<uintptr_t>( pawnprivate + offsets::Mesh );
	if ( !targetMesh )
		return;
	if ( !utils.isEnemyVis( targetMesh ) )
		return;

	FVector Head3D;
	FVector2D Head2D;

	Head3D = bone.GetBoneLoc( targetMesh , 110 );

	ImGuiIO& io = ImGui::GetIO( );
	ImVec2 screenCenter( io.DisplaySize.x / 2 , io.DisplaySize.y / 2 );
	Head2D = sdk.ProjectWorldToScreen( Head3D );

	ImVec2 target = CalculateAimOffset( Head2D , screenCenter , aim.smoothness , io.DisplaySize.x , io.DisplaySize.y );
	mem::MoveMouse( target.x , target.y );
}