#pragma once

namespace lib
{
	/**
	 * Available player actions, usually in a list of disallowed actions
	 */
	enum class player_action
	{
		/**
		 * Invalid action
		 */
		unknown,

		/**
		 * Controlling playback
		 */
		interrupting_playback,

		/**
		 * Pause current track
		 */
		pausing,

		/**
		 * Resume current track
		 */
		resuming,

		/**
		 * Seek in current track
		 */
		seeking,

		/**
		 * Skip to next track
		 */
		skipping_next,

		/**
		 * Go back to previous track
		 */
		skipping_prev,

		/**
		 * Enable/disable repeat of current context
		 */
		toggling_repeat_context,

		/**
		 * Enable/disable shuffle
		 */
		toggling_shuffle,

		/**
		 * Enable/disable repeat of current track
		 */
		toggling_repeat_track,

		/**
		 * Select another device
		 */
		transferring_playback,
	};
}
