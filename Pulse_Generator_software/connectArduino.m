function a = connectArduino()
    % reconnect arduino
    vars = evalin('base','whos');
    if any(strcmp({vars.class},'arduino'))
        arduinoName = vars(strcmp({vars.class},'arduino')).name;
        evalin('base',sprintf('clear(''%s'')',arduinoName));
    end
    
    try a = arduino();
    catch ME
        warndlg('Arduino cannot be detected')
        a = [];
        return
    end
%     assignin('base','a',a);
    % initialize pins by activating once
    dpins = cellfun(@any,regexp(a.AvailablePins,'D\d'));
%     for i=1:length(dpins)
%         if dpins(i)
%             trgPulse(a,a.AvailablePins{i});
%         end
%     end
    fprintf('%s is connected\n',a.Board)
end
