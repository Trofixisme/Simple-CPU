int main(){
    int clock=0;
    while(!halted) {
        
        fetch();
        decode();
        excute();
        
        clock++;
//        sleep(1);
        
    }
}
