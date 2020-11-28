## TicTacToe

A very simple game everyone should know. 
I wrote it to test a few things out.
A human player plays against the AI.
Can you beat the AI? ;)

#### Version

This is the **C++** version of the game.
You can find the twin repo written in **Java** here on my github or directly https://github.com/SauronTs/TicTacToe-Java

#### Things used
No graphics libraries. Only simple text output.
The AI decides their moves using the minimax algorithm, whereby the complete tree is computated and used.

#### Performance test
AI vs AI: 
You can the test the performance of this program on different systems and see the difference between C++ and Java.
This project is just for fun, so don't expect super optimizations etc...

**C++ version measured with time on macOS Catalina**
```
Player: 0
AI: 0
No: 1000
./Test 1000  17,78s user 0,01s system 99% cpu 17,811 total
```

**Java version measured with time on macOS Catalina**
```
Player: 0
AI: 0
No: 1000
java Main 1000  28,47s user 0,06s system 100% cpu 28,391 total
```

Please keep in mind that the AI will always achieve a draw. The because both AI's are using the full minimax algorithm.

Note: Its called "Player" and "AI" because of the human playable version which is on the main branch. I didn't change it.

#### Signing
Testing the commit signing for github.
