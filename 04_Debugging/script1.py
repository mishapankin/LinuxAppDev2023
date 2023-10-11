import gdb

result_filename = "range1.txt"

class MyBp1(gdb.Breakpoint):
    def __init__(self, location):
        super(MyBp1, self).__init__(location)
    
    def stop(self):
        start = gdb.parse_and_eval("I->start")
        stop = gdb.parse_and_eval("I->stop")
        step = gdb.parse_and_eval("I->step")
        
        with open(result_filename, "w") as f:
            f.write(f"{start} {stop} {step}\n")
            
        return False

class MyBp2(gdb.Breakpoint):
    def __init__(self, location):
        super(MyBp2, self).__init__(location)
    
    def stop(self):
        current = gdb.parse_and_eval("I->current")
        if current % 5 != 0:
            return False
        
        with open(result_filename, "a") as f:
            f.write(f"{current} ")
            
        return False

MyBp1("range.c:50")
MyBp2("range.c:52")
