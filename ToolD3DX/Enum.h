#pragma once

// ���� Ÿ��
enum E_GROUND_TYPE {
	E_GROUND_TYPE_BEGIN,
    E_SOIL_GROUND = E_GROUND_TYPE_BEGIN,		// �� ����
    //E_WATER_GROUND,							// �� ����
    E_GRASS_GROUND,								// Ǯ ����
    E_STONE_GROUND,								// �� ����
	E_GROUND_TYPE_MAX
};

// �̺�Ʈ Ʈ�� Ÿ��
enum E_EVENT_TRAP_TYPE {
    E_EVENT_TRAP_NONE,
    E_MONSTER_TRAP
};

// ������Ʈ Ÿ��
enum E_OBJECT_TYPE {
    E_STONE,
    E_TREE,
    E_HOUSE,
    E_SIGNPOST   // ����ǥ
};

// ������Ʈ ���� (�浹����, �ı�����)
enum E_OBJECT_PROPERTY {
    E_DES_COL,              // �ı����� �浹����
    E_DES_NONCOL,           // �ı����� �浹�Ұ�
    E_NONDES_COL,           // �ı��Ұ� �浹����
    E_NONDES_NONCOL,        // �ı��Ұ� �浹�Ұ�
    E_OBJ_NONE              // ������Ʈ ����
};

// ���� ������
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

// ���� ���� Ÿ��
enum E_TERRAIN_EDIT_TYPE {
	E_TER_EDIT_BEGIN,
	E_TER_EDIT_HEIGHT = E_TER_EDIT_BEGIN,		// �⺻ ����
	E_TER_EDIT_RETURN,		            // �ǵ�����
    E_TER_EDIT_FIXED_HEIGHT,			// ���� ���̷� ����
	E_TER_EDIT_FLAT,		            // �����۾�
	E_TER_EDIT_TRIM,        			// ���� �ٵ��
    E_TER_EDIT_RESET                    // ����
};

// �� Ÿ��
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

// ������ �귯�� Ÿ��
enum E_TER_BRUSH_TYPE {
    E_TER_BRUSH_SMOOTH,     // �ε巴��
    E_TER_BRUSH_SHARP       // ��ī�Ӱ�
};

// �ؽ��� �ٸ��� Ÿ��
enum E_DRAW_TYPE {
    E_DRAW_BRUSH,
    E_DRAW_SPRAY,
    E_DRAW_ERASE,
    E_DRAW_NONE
};

// ������Ʈ �� ������Ʈ ���� ��ư ���� 
enum E_OBJECT_BUTTON_STATE
{
    E_OBJ_TAB_BTN_LOCATE, 
    E_OBJ_TAB_BTN_RELOCATE, 
    E_OBJ_TAB_BTN_REMOVE, 
    E_OBJ_TAB_BTN_MAX
};

// ������Ʈ �� ��� ���� ��ư ����
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