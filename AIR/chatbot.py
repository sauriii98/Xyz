from nltk.chat.util import Chat, reflections

pairs=[
		[ r"hello(.*)",

			["hello %1",]
		],

		[ r"how are you(.*)",

			["fine",]
		],

		[ r"anything else",

			["nope",]
		],

		[ r"then leave",

			["ok fine",]
		],
	]


def chatbot():
	chat = Chat(paires,reflections)
	chat.converse()

chatbot()