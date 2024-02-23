#include "playwright_dialogue_manager.h"

#include "playwright_textbox.h"
#include "playwright_textbox_response.h"
#include "playwright_dialogue.h"

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

void PlaywrightDialogueManager::_bind_methods() {
	


	ADD_SIGNAL(MethodInfo("dialogue_complete"));
	ADD_SIGNAL(MethodInfo("dialogue_trigger"));
	ADD_SIGNAL(MethodInfo("end_branch"));
}

PlaywrightDialogueManager::PlaywrightDialogueManager() {
	branch_index = 0;

	player_selection = 0;

	branch_index = 0;
	branch_ended = false;
	line_index = 0;

	is_npc_dialogue_active = false;
	is_player_dialogue_active = false;
	can_advance_line = false;
}

PlaywrightDialogueManager::~PlaywrightDialogueManager() {

}

void PlaywrightDialogueManager::_ready() {
	if (Engine::get_singleton()->is_editor_hint()) {
		set_process_mode(Node::ProcessMode::PROCESS_MODE_DISABLED);
	}
	else {
		UtilityFunctions::print("is this thing on?");

		ResourceLoader* re_lo = ResourceLoader::get_singleton();

		textbox_scene = re_lo->load("res://addons/playwright_runtime/scenes/playwright_textbox.tscn");
		textbox_response_scene = re_lo->load("res://addons/playwright_runtime/scenes/playwright_textbox_response.tscn");

		textbox_inst = Object::cast_to<PlaywrightTextbox>(textbox_scene->instantiate());
		textbox_response_inst = Object::cast_to<PlaywrightTextboxResponse>(textbox_response_scene->instantiate());
	}
}

void PlaywrightDialogueManager::_unhandled_input(const Ref<InputEvent> &event) {
	// if the right key is pressed, determine how to proceed through dialogue.
	if (event->is_action_pressed("gui_select")) {
		// if there's a player dialogue, pass in the player choice (branch) and reload to continue on.
		if (is_player_dialogue_active) {
			advance_dlg_and_reload_textbox(textbox_response_inst->get_player_selection());
		}
		// if there's an NPC dialogue, decide to reload with the correct branch OR display the rest of the line first.
		else if (is_npc_dialogue_active) {
			if (can_advance_line) {
				advance_dlg_and_reload_textbox(branch_index);
			}
			// if the key is pressed early before the line can be advanced, display the rest of the line all at once.
			else {
				textbox_inst->display_line();
			}
		}
	}
}

void PlaywrightDialogueManager::initiate_dialogue(Ref<PlaywrightDialogue> &dlg, int dlg_index) {

}

void PlaywrightDialogueManager::end_dialogue() {

}

void PlaywrightDialogueManager::continue_dialogue(Ref<PlaywrightDialogue> &dlg, int dlg_index, TypedArray<int> ending_branch_positions) {

}

int PlaywrightDialogueManager::recalculate_branch_pos(int dlg_index, TypedArray<int> ending_branch_positions) {
	return 0;
}

void PlaywrightDialogueManager::show_textbox(PlaywrightDialogue::DIALOGUE_TYPE dlg_type) {

}

void PlaywrightDialogueManager::advance_dlg_and_reload_textbox(int dlg_index) {

}

int PlaywrightDialogueManager::realign_npc_dlg_index(int dlg_index) {
	return 0;
}

int PlaywrightDialogueManager::realign_player_dlg_index(int dlg_index) {
	return 0;
}

int PlaywrightDialogueManager::return_dlg_index_in_1d_array_format(int dlg_index) {
	return 0;
}

void PlaywrightDialogueManager::destroy_textboxes() {

}