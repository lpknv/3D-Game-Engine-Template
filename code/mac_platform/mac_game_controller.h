void
MacProcessGameControllerButton(game_button_state *oldState, game_button_state *newState,
                               int32_t isDown) 
{
    newState->EndedDown = isDown;
    newState->HalfTransitionCount += ((newState->EndedDown == oldState->EndedDown)?0:1);
}
