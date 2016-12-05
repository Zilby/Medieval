#ifndef PING_RELEVANTEVENT_H
#define PING_RELEVANTEVENT_H

namespace ping {

/**
 * Relevent Event Enumeration.
 * @author Ken Baclawski
 */
enum class RelevantEvent {
  /** No relevant event occurred. */ NONE,
  /** The user requested that the program quit. */ QUIT
};

}

#endif
