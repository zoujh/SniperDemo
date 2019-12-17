1, Generate Light.root
$ python generate.py --evtmax 100 --source Light

2, Generate Charge.root
$ python generate.py --evtmax 100 --source Charge

3, Read Light.root/Charge.root
$ python read.py --evtmax 100 --source Light/Charge

4, Build physical event and check
$ python build.py

5, TODO: save the physical event to disk
