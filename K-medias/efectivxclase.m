function F = efectivxclase(O)
  c1 = 0;
  c2 = 0;
  c3 = 0;
  for i = 1 : length(O)
    if O(i, 2) == 1
      c1 = c1 + 1;
    end
    if O(i, 2) == 2
      c2 = c2 + 1;
    end
    if O(i, 2) == 3
      c3 = c3 + 1;
    end
  end
  F = max([c1, c2, c3])/length(O);
end
