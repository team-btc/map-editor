#pragma once

// 지형 타입
enum E_GROUND_TYPE {
	E_GROUND_TYPE_BEGIN,
    E_SOIL_GROUND = E_GROUND_TYPE_BEGIN,		// 흙 지형
    //E_WATER_GROUND,							// 물 지형
    E_GRASS_GROUND,								// 풀 지형
    E_STONE_GROUND,								// 돌 지형
	E_GROUND_TYPE_MAX
};

// 이벤트 트랩 타입
enum E_EVENT_TRAP_TYPE {
    E_EVENT_TRAP_NONE,
    E_MONSTER_TRAP
};

// 오브젝트 타입
enum E_OBJECT_TYPE {
    E_STONE,
    E_TREE,
    E_HOUSE,
    E_SIGNPOST   // 이정표
};

// 오브젝트 성질 (충돌여부, 파괴여부)
enum E_OBJECT_PROPERTY {
    E_DES_COL,              // 파괴가능 충돌가능
    E_DES_NONCOL,           // 파괴가능 충돌불가
    E_NONDES_COL,           // 파괴불가 충돌가능
    E_NONDES_NONCOL,        // 파괴불가 충돌불가
    E_OBJ_NONE              // 오브젝트 없음
};

// 지형 사이즈
enum E_MAP_SIZE {
	E_MAP_SIZE_BEGIN,
	E_SIZE_64 = E_MAP_SIZE_BEGIN,
	E_SIZE_128,
	E_SIZE_192,
	E_SIZE_256,
	E_SIZE_320,
	E_SIZE_384,
	E_SIZE_448,
	E_SIZE_512,
	E_SIZE_576,
	E_SIZE_640,
	E_SIZE_704,
	E_SIZE_768,
	E_SIZE_832,
	E_SIZE_896,
	E_SIZE_960,
	E_SIZE_1024,
	E_MAP_SIZE_MAX
};

// 지형 편집 타입
enum E_TERRAIN_EDIT_TYPE {
	E_TER_EDIT_BEGIN,
	E_TER_EDIT_HEIGHT = E_TER_EDIT_BEGIN,		// 기본 편집
	E_TER_EDIT_RETURN,		            // 되돌리기
    E_TER_EDIT_FIXED_HEIGHT,			// 고정 높이로 편집
	E_TER_EDIT_FLAT,		            // 평지작업
	E_TER_EDIT_TRIM,        			// 지형 다듬기
    E_TER_EDIT_RESET                    // 리셋
};

// 탭 타입
enum E_TAB_TYPE {
    E_CREATE_TAB,
    E_TERRAIN_TAB,
    E_TEXTURE_TAB,
    E_WATER_TAB,
    E_OBJECT_TAB
};

enum E_UP_DOWN {
    E_UP,
    E_DOWN
};

// 지형맵 브러쉬 타입
enum E_TER_BRUSH_TYPE {
    E_TER_BRUSH_SMOOTH,     // 부드럽게
    E_TER_BRUSH_SHARP       // 날카롭게
};

// 텍스쳐 바르는 타입
enum E_DRAW_TYPE {
    E_DRAW_BRUSH,
    E_DRAW_SPRAY,
    E_DRAW_ERASE,
    E_DRAW_NONE
};

// 오브젝트 탭 오브젝트 에딧 버튼 상태 
enum E_OBJECT_BUTTON_STATE
{
    E_OBJ_TAB_BTN_LOCATE, 
    E_OBJ_TAB_BTN_RELOCATE, 
    E_OBJ_TAB_BTN_REMOVE, 
    E_OBJ_TAB_BTN_MAX
};

// 오브젝트 탭 블록 에딧 버튼 상태
enum E_BLOCK_BUTTON_STATE
{
    E_BLOCK_BTN_NEW, 
    E_BLOCK_BTN_PROGRESS, 
    E_BLOCK_BTN_MODIFY,
    E_BLOCK_BTN_LATEST_DELETE,
    E_BLOCK_BTN_DELETE,
    E_BLOCK_BTN_END, 
    E_BLOCK_BTN_MAX
};