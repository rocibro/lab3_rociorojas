/*
 * FSM.h
 *
 *  Created on: May 2, 2018
 *      Author: VIDEOJUEGOS UTALCA
 */

#ifndef FSM_H_
#define FSM_H_
#include <list>
#include <memory>
#include "Character.h"
#include "GameState.h"

class FSMState;

class FSMTransition {
public:
	virtual bool isValid(const GameState& gs)=0 ; //se cumple la condición
	virtual std::shared_ptr<FSMState> getNextState()=0; //a que estado salto?
	virtual void onTransition(const GameState& gs); 
	virtual ~FSMTransition();
};


class FSMState {

public:
	FSMState(std::shared_ptr<Character> _character);
	virtual void onEnter(const GameState& gs); //Se llama al entrar al estado
	virtual Move onUpdate(const GameState& gs)=0; //se llama cada frame meintras me encuentro en el estado
	virtual void onExit(const GameState& gs); //se llama al salir del estado
	virtual ~FSMState();
	void addTransition(std::shared_ptr<FSMTransition> t);
	std::shared_ptr<FSMTransition> getActiveTransition(const GameState& gs); //revisa transiciones y devuelve la primera válida
protected:
	std::shared_ptr<Character> character;
	std::list<std::shared_ptr<FSMTransition>> transitions;
};



class FiniteStateMachine {

public:
	FiniteStateMachine(std::shared_ptr<Character> _character); //el "loop" de la maquina completa
	virtual Move update(const GameState& gs)=0;
	virtual ~FiniteStateMachine() ;
protected:
	std::shared_ptr<Character> character;
	std::list<std::shared_ptr<FSMState>> states;
	std::shared_ptr<FSMState> initialState;
	std::shared_ptr<FSMState> activeState;
};

#endif /* FSM_H_ */
