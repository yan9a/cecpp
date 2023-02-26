function ofunc()
  [X,Y] = meshgrid(-10:0.25:10,-10:0.25:10);
  f = sinc(sqrt((X/pi).^2+(Y/pi).^2));
  hFig1 = figure(1);
  mesh(X,Y,f);
  axis([-10 10 -10 10 -0.3 1]);
  xlabel('X');
  ylabel('Y');
  zlabel('sinc(R)');
  hidden off;
    
  load test.csv;
  x=test(:,1);
  y=test(:,2);
  z=calcu(x);
  %-------------------------------------------------------------------------
  %Plot 
  hFig2 = figure(2);
  set(hFig2, 'Position', [50 100 600 400]);
  plot(x,y,'-gs','LineWidth',1,'MarkerEdgeColor','g','MarkerFaceColor','g','MarkerSize',2);
            
  hold on;
  %plot(x,z,'-go','LineWidth',1,'MarkerEdgeColor','g','MarkerFaceColor','g','MarkerSize',2)
  stairs(x,z,'-rd','LineWidth',2,'MarkerEdgeColor','r','MarkerFaceColor','r','MarkerSize',2)
  hold off;
  grid on;
  legend('y','z','Location','northeast')
  title('x^2');
  xlabel('x ');
  ylabel('y');
  axis([0 100 0 10000]);
  set(gca,'XTick',(0:10:100));
  set(gca,'YTick',(0:2000:10000));
  %-------------------------------------------------------------------------
  % d = [x y z];
  % csvwrite("result.csv",d);
  
  printf("Press anykey to exit!\n");
  pause 
endfunction

function z=calcu(x)
  w=2*pi*0.02;
  s=x.*x;
  z=s+s.*sin(w.*x);
endfunction