function offPin(a,outpin)
    if ~isa(a,'arduino')
        error('first argument must be arduino object')
    end
    if ~isa(outpin,'char')
        error('second argument must be char')
    end
    
    a.writeDigitalPin(outpin,0)    
end