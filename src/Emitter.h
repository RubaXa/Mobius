//
//  Emitter.h
//

#ifndef Mobius_Emitter_h
#define Mobius_Emitter_h


typedef void (*callback)(const int id);

namespace Mobius {

	class Emitter {
	private:
		//
		// Listener
		//
		class Listener {
		public:
			int id = 0;
			callback handler;
		};

		// Список слушателей
		List <Emitter::Listener> listeners;


	public:
		static const int TEST_EVENT = 0;


		static int nextId() {
			static int gid = 0;
			return ++gid;
		}


		// Подписаться на событие
		void bind(int id, callback handler) {
			Listener *listener = new Listener();

			listener->id = id;
			listener->handler = handler;

			this->listeners.push(listener);
		}


		// Испустить событие
		void trigger(int id) {
			for (int i = 0; i < this->listeners.size(); i++) {
				Emitter::Listener *listener = this->listeners.get(i);

				if (listener->id == id) {
					listener->handler(id);
				}
			}
		}
	};

}

#endif
