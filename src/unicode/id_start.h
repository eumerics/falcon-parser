int is_unicode_id_start(uint32_t c){
   if(c < 0xA7F5){
      if(c < 0x0F88){
         if(c < 0x0A85){
            if(c < 0x07B1){
               if(c < 0x03A3){
                  if(c < 0x02EC){
                     if(c < 0x00C0){
                        if(c < 0x00B5){
                           if(c < 0x00AA){
                              if(c < 0x0061){
                                 return (c >= 0x0041 && c <= 0x005A);
                              } else {
                                 return (c >= 0x0061 && c <= 0x007A);
                              }
                           } else {
                              return (c >= 0x00AA && c <= 0x00AA);
                           }
                        } else {
                           if(c < 0x00BA){
                              return (c >= 0x00B5 && c <= 0x00B5);
                           } else {
                              return (c >= 0x00BA && c <= 0x00BA);
                           }
                        }
                     } else {
                        if(c < 0x02C6){
                           if(c < 0x00F8){
                              if(c < 0x00D8){
                                 return (c >= 0x00C0 && c <= 0x00D6);
                              } else {
                                 return (c >= 0x00D8 && c <= 0x00F6);
                              }
                           } else {
                              return (c >= 0x00F8 && c <= 0x02C1);
                           }
                        } else {
                           if(c < 0x02E0){
                              return (c >= 0x02C6 && c <= 0x02D1);
                           } else {
                              return (c >= 0x02E0 && c <= 0x02E4);
                           }
                        }
                     }
                  } else {
                     if(c < 0x037F){
                        if(c < 0x0376){
                           if(c < 0x0370){
                              if(c < 0x02EE){
                                 return (c >= 0x02EC && c <= 0x02EC);
                              } else {
                                 return (c >= 0x02EE && c <= 0x02EE);
                              }
                           } else {
                              return (c >= 0x0370 && c <= 0x0374);
                           }
                        } else {
                           if(c < 0x037A){
                              return (c >= 0x0376 && c <= 0x0377);
                           } else {
                              return (c >= 0x037A && c <= 0x037D);
                           }
                        }
                     } else {
                        if(c < 0x038C){
                           if(c < 0x0388){
                              if(c < 0x0386){
                                 return (c >= 0x037F && c <= 0x037F);
                              } else {
                                 return (c >= 0x0386 && c <= 0x0386);
                              }
                           } else {
                              return (c >= 0x0388 && c <= 0x038A);
                           }
                        } else {
                           if(c < 0x038E){
                              return (c >= 0x038C && c <= 0x038C);
                           } else {
                              return (c >= 0x038E && c <= 0x03A1);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x0671){
                     if(c < 0x0560){
                        if(c < 0x0531){
                           if(c < 0x048A){
                              if(c < 0x03F7){
                                 return (c >= 0x03A3 && c <= 0x03F5);
                              } else {
                                 return (c >= 0x03F7 && c <= 0x0481);
                              }
                           } else {
                              return (c >= 0x048A && c <= 0x052F);
                           }
                        } else {
                           if(c < 0x0559){
                              return (c >= 0x0531 && c <= 0x0556);
                           } else {
                              return (c >= 0x0559 && c <= 0x0559);
                           }
                        }
                     } else {
                        if(c < 0x0620){
                           if(c < 0x05EF){
                              if(c < 0x05D0){
                                 return (c >= 0x0560 && c <= 0x0588);
                              } else {
                                 return (c >= 0x05D0 && c <= 0x05EA);
                              }
                           } else {
                              return (c >= 0x05EF && c <= 0x05F2);
                           }
                        } else {
                           if(c < 0x066E){
                              return (c >= 0x0620 && c <= 0x064A);
                           } else {
                              return (c >= 0x066E && c <= 0x066F);
                           }
                        }
                     }
                  } else {
                     if(c < 0x06FF){
                        if(c < 0x06EE){
                           if(c < 0x06E5){
                              if(c < 0x06D5){
                                 return (c >= 0x0671 && c <= 0x06D3);
                              } else {
                                 return (c >= 0x06D5 && c <= 0x06D5);
                              }
                           } else {
                              return (c >= 0x06E5 && c <= 0x06E6);
                           }
                        } else {
                           if(c < 0x06FA){
                              return (c >= 0x06EE && c <= 0x06EF);
                           } else {
                              return (c >= 0x06FA && c <= 0x06FC);
                           }
                        }
                     } else {
                        if(c < 0x0712){
                           if(c < 0x0710){
                              return (c >= 0x06FF && c <= 0x06FF);
                           } else {
                              return (c >= 0x0710 && c <= 0x0710);
                           }
                        } else {
                           if(c < 0x074D){
                              return (c >= 0x0712 && c <= 0x072F);
                           } else {
                              return (c >= 0x074D && c <= 0x07A5);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x09AA){
                  if(c < 0x08A0){
                     if(c < 0x081A){
                        if(c < 0x07FA){
                           if(c < 0x07F4){
                              if(c < 0x07CA){
                                 return (c >= 0x07B1 && c <= 0x07B1);
                              } else {
                                 return (c >= 0x07CA && c <= 0x07EA);
                              }
                           } else {
                              return (c >= 0x07F4 && c <= 0x07F5);
                           }
                        } else {
                           if(c < 0x0800){
                              return (c >= 0x07FA && c <= 0x07FA);
                           } else {
                              return (c >= 0x0800 && c <= 0x0815);
                           }
                        }
                     } else {
                        if(c < 0x0840){
                           if(c < 0x0828){
                              if(c < 0x0824){
                                 return (c >= 0x081A && c <= 0x081A);
                              } else {
                                 return (c >= 0x0824 && c <= 0x0824);
                              }
                           } else {
                              return (c >= 0x0828 && c <= 0x0828);
                           }
                        } else {
                           if(c < 0x0860){
                              return (c >= 0x0840 && c <= 0x0858);
                           } else {
                              return (c >= 0x0860 && c <= 0x086A);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0958){
                        if(c < 0x093D){
                           if(c < 0x0904){
                              if(c < 0x08B6){
                                 return (c >= 0x08A0 && c <= 0x08B4);
                              } else {
                                 return (c >= 0x08B6 && c <= 0x08C7);
                              }
                           } else {
                              return (c >= 0x0904 && c <= 0x0939);
                           }
                        } else {
                           if(c < 0x0950){
                              return (c >= 0x093D && c <= 0x093D);
                           } else {
                              return (c >= 0x0950 && c <= 0x0950);
                           }
                        }
                     } else {
                        if(c < 0x098F){
                           if(c < 0x0985){
                              if(c < 0x0971){
                                 return (c >= 0x0958 && c <= 0x0961);
                              } else {
                                 return (c >= 0x0971 && c <= 0x0980);
                              }
                           } else {
                              return (c >= 0x0985 && c <= 0x098C);
                           }
                        } else {
                           if(c < 0x0993){
                              return (c >= 0x098F && c <= 0x0990);
                           } else {
                              return (c >= 0x0993 && c <= 0x09A8);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x0A0F){
                     if(c < 0x09DC){
                        if(c < 0x09BD){
                           if(c < 0x09B6){
                              if(c < 0x09B2){
                                 return (c >= 0x09AA && c <= 0x09B0);
                              } else {
                                 return (c >= 0x09B2 && c <= 0x09B2);
                              }
                           } else {
                              return (c >= 0x09B6 && c <= 0x09B9);
                           }
                        } else {
                           if(c < 0x09CE){
                              return (c >= 0x09BD && c <= 0x09BD);
                           } else {
                              return (c >= 0x09CE && c <= 0x09CE);
                           }
                        }
                     } else {
                        if(c < 0x09FC){
                           if(c < 0x09F0){
                              if(c < 0x09DF){
                                 return (c >= 0x09DC && c <= 0x09DD);
                              } else {
                                 return (c >= 0x09DF && c <= 0x09E1);
                              }
                           } else {
                              return (c >= 0x09F0 && c <= 0x09F1);
                           }
                        } else {
                           if(c < 0x0A05){
                              return (c >= 0x09FC && c <= 0x09FC);
                           } else {
                              return (c >= 0x0A05 && c <= 0x0A0A);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0A38){
                        if(c < 0x0A32){
                           if(c < 0x0A2A){
                              if(c < 0x0A13){
                                 return (c >= 0x0A0F && c <= 0x0A10);
                              } else {
                                 return (c >= 0x0A13 && c <= 0x0A28);
                              }
                           } else {
                              return (c >= 0x0A2A && c <= 0x0A30);
                           }
                        } else {
                           if(c < 0x0A35){
                              return (c >= 0x0A32 && c <= 0x0A33);
                           } else {
                              return (c >= 0x0A35 && c <= 0x0A36);
                           }
                        }
                     } else {
                        if(c < 0x0A5E){
                           if(c < 0x0A59){
                              return (c >= 0x0A38 && c <= 0x0A39);
                           } else {
                              return (c >= 0x0A59 && c <= 0x0A5C);
                           }
                        } else {
                           if(c < 0x0A72){
                              return (c >= 0x0A5E && c <= 0x0A5E);
                           } else {
                              return (c >= 0x0A72 && c <= 0x0A74);
                           }
                        }
                     }
                  }
               }
            }
         } else {
            if(c < 0x0C85){
               if(c < 0x0B83){
                  if(c < 0x0B05){
                     if(c < 0x0AB5){
                        if(c < 0x0AAA){
                           if(c < 0x0A93){
                              if(c < 0x0A8F){
                                 return (c >= 0x0A85 && c <= 0x0A8D);
                              } else {
                                 return (c >= 0x0A8F && c <= 0x0A91);
                              }
                           } else {
                              return (c >= 0x0A93 && c <= 0x0AA8);
                           }
                        } else {
                           if(c < 0x0AB2){
                              return (c >= 0x0AAA && c <= 0x0AB0);
                           } else {
                              return (c >= 0x0AB2 && c <= 0x0AB3);
                           }
                        }
                     } else {
                        if(c < 0x0AE0){
                           if(c < 0x0AD0){
                              if(c < 0x0ABD){
                                 return (c >= 0x0AB5 && c <= 0x0AB9);
                              } else {
                                 return (c >= 0x0ABD && c <= 0x0ABD);
                              }
                           } else {
                              return (c >= 0x0AD0 && c <= 0x0AD0);
                           }
                        } else {
                           if(c < 0x0AF9){
                              return (c >= 0x0AE0 && c <= 0x0AE1);
                           } else {
                              return (c >= 0x0AF9 && c <= 0x0AF9);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0B35){
                        if(c < 0x0B2A){
                           if(c < 0x0B13){
                              if(c < 0x0B0F){
                                 return (c >= 0x0B05 && c <= 0x0B0C);
                              } else {
                                 return (c >= 0x0B0F && c <= 0x0B10);
                              }
                           } else {
                              return (c >= 0x0B13 && c <= 0x0B28);
                           }
                        } else {
                           if(c < 0x0B32){
                              return (c >= 0x0B2A && c <= 0x0B30);
                           } else {
                              return (c >= 0x0B32 && c <= 0x0B33);
                           }
                        }
                     } else {
                        if(c < 0x0B5F){
                           if(c < 0x0B5C){
                              if(c < 0x0B3D){
                                 return (c >= 0x0B35 && c <= 0x0B39);
                              } else {
                                 return (c >= 0x0B3D && c <= 0x0B3D);
                              }
                           } else {
                              return (c >= 0x0B5C && c <= 0x0B5D);
                           }
                        } else {
                           if(c < 0x0B71){
                              return (c >= 0x0B5F && c <= 0x0B61);
                           } else {
                              return (c >= 0x0B71 && c <= 0x0B71);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x0BD0){
                     if(c < 0x0B9C){
                        if(c < 0x0B92){
                           if(c < 0x0B8E){
                              if(c < 0x0B85){
                                 return (c >= 0x0B83 && c <= 0x0B83);
                              } else {
                                 return (c >= 0x0B85 && c <= 0x0B8A);
                              }
                           } else {
                              return (c >= 0x0B8E && c <= 0x0B90);
                           }
                        } else {
                           if(c < 0x0B99){
                              return (c >= 0x0B92 && c <= 0x0B95);
                           } else {
                              return (c >= 0x0B99 && c <= 0x0B9A);
                           }
                        }
                     } else {
                        if(c < 0x0BA8){
                           if(c < 0x0BA3){
                              if(c < 0x0B9E){
                                 return (c >= 0x0B9C && c <= 0x0B9C);
                              } else {
                                 return (c >= 0x0B9E && c <= 0x0B9F);
                              }
                           } else {
                              return (c >= 0x0BA3 && c <= 0x0BA4);
                           }
                        } else {
                           if(c < 0x0BAE){
                              return (c >= 0x0BA8 && c <= 0x0BAA);
                           } else {
                              return (c >= 0x0BAE && c <= 0x0BB9);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0C3D){
                        if(c < 0x0C12){
                           if(c < 0x0C0E){
                              if(c < 0x0C05){
                                 return (c >= 0x0BD0 && c <= 0x0BD0);
                              } else {
                                 return (c >= 0x0C05 && c <= 0x0C0C);
                              }
                           } else {
                              return (c >= 0x0C0E && c <= 0x0C10);
                           }
                        } else {
                           if(c < 0x0C2A){
                              return (c >= 0x0C12 && c <= 0x0C28);
                           } else {
                              return (c >= 0x0C2A && c <= 0x0C39);
                           }
                        }
                     } else {
                        if(c < 0x0C60){
                           if(c < 0x0C58){
                              return (c >= 0x0C3D && c <= 0x0C3D);
                           } else {
                              return (c >= 0x0C58 && c <= 0x0C5A);
                           }
                        } else {
                           if(c < 0x0C80){
                              return (c >= 0x0C60 && c <= 0x0C61);
                           } else {
                              return (c >= 0x0C80 && c <= 0x0C80);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x0DBD){
                  if(c < 0x0D0E){
                     if(c < 0x0CBD){
                        if(c < 0x0CAA){
                           if(c < 0x0C92){
                              if(c < 0x0C8E){
                                 return (c >= 0x0C85 && c <= 0x0C8C);
                              } else {
                                 return (c >= 0x0C8E && c <= 0x0C90);
                              }
                           } else {
                              return (c >= 0x0C92 && c <= 0x0CA8);
                           }
                        } else {
                           if(c < 0x0CB5){
                              return (c >= 0x0CAA && c <= 0x0CB3);
                           } else {
                              return (c >= 0x0CB5 && c <= 0x0CB9);
                           }
                        }
                     } else {
                        if(c < 0x0CF1){
                           if(c < 0x0CE0){
                              if(c < 0x0CDE){
                                 return (c >= 0x0CBD && c <= 0x0CBD);
                              } else {
                                 return (c >= 0x0CDE && c <= 0x0CDE);
                              }
                           } else {
                              return (c >= 0x0CE0 && c <= 0x0CE1);
                           }
                        } else {
                           if(c < 0x0D04){
                              return (c >= 0x0CF1 && c <= 0x0CF2);
                           } else {
                              return (c >= 0x0D04 && c <= 0x0D0C);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0D5F){
                        if(c < 0x0D4E){
                           if(c < 0x0D3D){
                              if(c < 0x0D12){
                                 return (c >= 0x0D0E && c <= 0x0D10);
                              } else {
                                 return (c >= 0x0D12 && c <= 0x0D3A);
                              }
                           } else {
                              return (c >= 0x0D3D && c <= 0x0D3D);
                           }
                        } else {
                           if(c < 0x0D54){
                              return (c >= 0x0D4E && c <= 0x0D4E);
                           } else {
                              return (c >= 0x0D54 && c <= 0x0D56);
                           }
                        }
                     } else {
                        if(c < 0x0D9A){
                           if(c < 0x0D85){
                              if(c < 0x0D7A){
                                 return (c >= 0x0D5F && c <= 0x0D61);
                              } else {
                                 return (c >= 0x0D7A && c <= 0x0D7F);
                              }
                           } else {
                              return (c >= 0x0D85 && c <= 0x0D96);
                           }
                        } else {
                           if(c < 0x0DB3){
                              return (c >= 0x0D9A && c <= 0x0DB1);
                           } else {
                              return (c >= 0x0DB3 && c <= 0x0DBB);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x0EA7){
                     if(c < 0x0E81){
                        if(c < 0x0E32){
                           if(c < 0x0E01){
                              if(c < 0x0DC0){
                                 return (c >= 0x0DBD && c <= 0x0DBD);
                              } else {
                                 return (c >= 0x0DC0 && c <= 0x0DC6);
                              }
                           } else {
                              return (c >= 0x0E01 && c <= 0x0E30);
                           }
                        } else {
                           if(c < 0x0E40){
                              return (c >= 0x0E32 && c <= 0x0E33);
                           } else {
                              return (c >= 0x0E40 && c <= 0x0E46);
                           }
                        }
                     } else {
                        if(c < 0x0E8C){
                           if(c < 0x0E86){
                              if(c < 0x0E84){
                                 return (c >= 0x0E81 && c <= 0x0E82);
                              } else {
                                 return (c >= 0x0E84 && c <= 0x0E84);
                              }
                           } else {
                              return (c >= 0x0E86 && c <= 0x0E8A);
                           }
                        } else {
                           if(c < 0x0EA5){
                              return (c >= 0x0E8C && c <= 0x0EA3);
                           } else {
                              return (c >= 0x0EA5 && c <= 0x0EA5);
                           }
                        }
                     }
                  } else {
                     if(c < 0x0EDC){
                        if(c < 0x0EC0){
                           if(c < 0x0EBD){
                              if(c < 0x0EB2){
                                 return (c >= 0x0EA7 && c <= 0x0EB0);
                              } else {
                                 return (c >= 0x0EB2 && c <= 0x0EB3);
                              }
                           } else {
                              return (c >= 0x0EBD && c <= 0x0EBD);
                           }
                        } else {
                           if(c < 0x0EC6){
                              return (c >= 0x0EC0 && c <= 0x0EC4);
                           } else {
                              return (c >= 0x0EC6 && c <= 0x0EC6);
                           }
                        }
                     } else {
                        if(c < 0x0F40){
                           if(c < 0x0F00){
                              return (c >= 0x0EDC && c <= 0x0EDF);
                           } else {
                              return (c >= 0x0F00 && c <= 0x0F00);
                           }
                        } else {
                           if(c < 0x0F49){
                              return (c >= 0x0F40 && c <= 0x0F47);
                           } else {
                              return (c >= 0x0F49 && c <= 0x0F6C);
                           }
                        }
                     }
                  }
               }
            }
         }
      } else {
         if(c < 0x1F48){
            if(c < 0x170E){
               if(c < 0x128A){
                  if(c < 0x10A0){
                     if(c < 0x1061){
                        if(c < 0x1050){
                           if(c < 0x103F){
                              if(c < 0x1000){
                                 return (c >= 0x0F88 && c <= 0x0F8C);
                              } else {
                                 return (c >= 0x1000 && c <= 0x102A);
                              }
                           } else {
                              return (c >= 0x103F && c <= 0x103F);
                           }
                        } else {
                           if(c < 0x105A){
                              return (c >= 0x1050 && c <= 0x1055);
                           } else {
                              return (c >= 0x105A && c <= 0x105D);
                           }
                        }
                     } else {
                        if(c < 0x1075){
                           if(c < 0x106E){
                              if(c < 0x1065){
                                 return (c >= 0x1061 && c <= 0x1061);
                              } else {
                                 return (c >= 0x1065 && c <= 0x1066);
                              }
                           } else {
                              return (c >= 0x106E && c <= 0x1070);
                           }
                        } else {
                           if(c < 0x108E){
                              return (c >= 0x1075 && c <= 0x1081);
                           } else {
                              return (c >= 0x108E && c <= 0x108E);
                           }
                        }
                     }
                  } else {
                     if(c < 0x124A){
                        if(c < 0x10D0){
                           if(c < 0x10CD){
                              if(c < 0x10C7){
                                 return (c >= 0x10A0 && c <= 0x10C5);
                              } else {
                                 return (c >= 0x10C7 && c <= 0x10C7);
                              }
                           } else {
                              return (c >= 0x10CD && c <= 0x10CD);
                           }
                        } else {
                           if(c < 0x10FC){
                              return (c >= 0x10D0 && c <= 0x10FA);
                           } else {
                              return (c >= 0x10FC && c <= 0x1248);
                           }
                        }
                     } else {
                        if(c < 0x125A){
                           if(c < 0x1258){
                              if(c < 0x1250){
                                 return (c >= 0x124A && c <= 0x124D);
                              } else {
                                 return (c >= 0x1250 && c <= 0x1256);
                              }
                           } else {
                              return (c >= 0x1258 && c <= 0x1258);
                           }
                        } else {
                           if(c < 0x1260){
                              return (c >= 0x125A && c <= 0x125D);
                           } else {
                              return (c >= 0x1260 && c <= 0x1288);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x1380){
                     if(c < 0x12C2){
                        if(c < 0x12B8){
                           if(c < 0x12B2){
                              if(c < 0x1290){
                                 return (c >= 0x128A && c <= 0x128D);
                              } else {
                                 return (c >= 0x1290 && c <= 0x12B0);
                              }
                           } else {
                              return (c >= 0x12B2 && c <= 0x12B5);
                           }
                        } else {
                           if(c < 0x12C0){
                              return (c >= 0x12B8 && c <= 0x12BE);
                           } else {
                              return (c >= 0x12C0 && c <= 0x12C0);
                           }
                        }
                     } else {
                        if(c < 0x1312){
                           if(c < 0x12D8){
                              if(c < 0x12C8){
                                 return (c >= 0x12C2 && c <= 0x12C5);
                              } else {
                                 return (c >= 0x12C8 && c <= 0x12D6);
                              }
                           } else {
                              return (c >= 0x12D8 && c <= 0x1310);
                           }
                        } else {
                           if(c < 0x1318){
                              return (c >= 0x1312 && c <= 0x1315);
                           } else {
                              return (c >= 0x1318 && c <= 0x135A);
                           }
                        }
                     }
                  } else {
                     if(c < 0x1681){
                        if(c < 0x1401){
                           if(c < 0x13F8){
                              if(c < 0x13A0){
                                 return (c >= 0x1380 && c <= 0x138F);
                              } else {
                                 return (c >= 0x13A0 && c <= 0x13F5);
                              }
                           } else {
                              return (c >= 0x13F8 && c <= 0x13FD);
                           }
                        } else {
                           if(c < 0x166F){
                              return (c >= 0x1401 && c <= 0x166C);
                           } else {
                              return (c >= 0x166F && c <= 0x167F);
                           }
                        }
                     } else {
                        if(c < 0x16EE){
                           if(c < 0x16A0){
                              return (c >= 0x1681 && c <= 0x169A);
                           } else {
                              return (c >= 0x16A0 && c <= 0x16EA);
                           }
                        } else {
                           if(c < 0x1700){
                              return (c >= 0x16EE && c <= 0x16F8);
                           } else {
                              return (c >= 0x1700 && c <= 0x170C);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x1B05){
                  if(c < 0x18AA){
                     if(c < 0x1780){
                        if(c < 0x1760){
                           if(c < 0x1740){
                              if(c < 0x1720){
                                 return (c >= 0x170E && c <= 0x1711);
                              } else {
                                 return (c >= 0x1720 && c <= 0x1731);
                              }
                           } else {
                              return (c >= 0x1740 && c <= 0x1751);
                           }
                        } else {
                           if(c < 0x176E){
                              return (c >= 0x1760 && c <= 0x176C);
                           } else {
                              return (c >= 0x176E && c <= 0x1770);
                           }
                        }
                     } else {
                        if(c < 0x1820){
                           if(c < 0x17DC){
                              if(c < 0x17D7){
                                 return (c >= 0x1780 && c <= 0x17B3);
                              } else {
                                 return (c >= 0x17D7 && c <= 0x17D7);
                              }
                           } else {
                              return (c >= 0x17DC && c <= 0x17DC);
                           }
                        } else {
                           if(c < 0x1880){
                              return (c >= 0x1820 && c <= 0x1878);
                           } else {
                              return (c >= 0x1880 && c <= 0x18A8);
                           }
                        }
                     }
                  } else {
                     if(c < 0x1980){
                        if(c < 0x1950){
                           if(c < 0x1900){
                              if(c < 0x18B0){
                                 return (c >= 0x18AA && c <= 0x18AA);
                              } else {
                                 return (c >= 0x18B0 && c <= 0x18F5);
                              }
                           } else {
                              return (c >= 0x1900 && c <= 0x191E);
                           }
                        } else {
                           if(c < 0x1970){
                              return (c >= 0x1950 && c <= 0x196D);
                           } else {
                              return (c >= 0x1970 && c <= 0x1974);
                           }
                        }
                     } else {
                        if(c < 0x1A20){
                           if(c < 0x1A00){
                              if(c < 0x19B0){
                                 return (c >= 0x1980 && c <= 0x19AB);
                              } else {
                                 return (c >= 0x19B0 && c <= 0x19C9);
                              }
                           } else {
                              return (c >= 0x1A00 && c <= 0x1A16);
                           }
                        } else {
                           if(c < 0x1AA7){
                              return (c >= 0x1A20 && c <= 0x1A54);
                           } else {
                              return (c >= 0x1AA7 && c <= 0x1AA7);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x1CBD){
                     if(c < 0x1C00){
                        if(c < 0x1BAE){
                           if(c < 0x1B83){
                              if(c < 0x1B45){
                                 return (c >= 0x1B05 && c <= 0x1B33);
                              } else {
                                 return (c >= 0x1B45 && c <= 0x1B4B);
                              }
                           } else {
                              return (c >= 0x1B83 && c <= 0x1BA0);
                           }
                        } else {
                           if(c < 0x1BBA){
                              return (c >= 0x1BAE && c <= 0x1BAF);
                           } else {
                              return (c >= 0x1BBA && c <= 0x1BE5);
                           }
                        }
                     } else {
                        if(c < 0x1C80){
                           if(c < 0x1C5A){
                              if(c < 0x1C4D){
                                 return (c >= 0x1C00 && c <= 0x1C23);
                              } else {
                                 return (c >= 0x1C4D && c <= 0x1C4F);
                              }
                           } else {
                              return (c >= 0x1C5A && c <= 0x1C7D);
                           }
                        } else {
                           if(c < 0x1C90){
                              return (c >= 0x1C80 && c <= 0x1C88);
                           } else {
                              return (c >= 0x1C90 && c <= 0x1CBA);
                           }
                        }
                     }
                  } else {
                     if(c < 0x1D00){
                        if(c < 0x1CF5){
                           if(c < 0x1CEE){
                              if(c < 0x1CE9){
                                 return (c >= 0x1CBD && c <= 0x1CBF);
                              } else {
                                 return (c >= 0x1CE9 && c <= 0x1CEC);
                              }
                           } else {
                              return (c >= 0x1CEE && c <= 0x1CF3);
                           }
                        } else {
                           if(c < 0x1CFA){
                              return (c >= 0x1CF5 && c <= 0x1CF6);
                           } else {
                              return (c >= 0x1CFA && c <= 0x1CFA);
                           }
                        }
                     } else {
                        if(c < 0x1F18){
                           if(c < 0x1E00){
                              return (c >= 0x1D00 && c <= 0x1DBF);
                           } else {
                              return (c >= 0x1E00 && c <= 0x1F15);
                           }
                        } else {
                           if(c < 0x1F20){
                              return (c >= 0x1F18 && c <= 0x1F1D);
                           } else {
                              return (c >= 0x1F20 && c <= 0x1F45);
                           }
                        }
                     }
                  }
               }
            }
         } else {
            if(c < 0x2D2D){
               if(c < 0x2107){
                  if(c < 0x1FC6){
                     if(c < 0x1F5F){
                        if(c < 0x1F5B){
                           if(c < 0x1F59){
                              if(c < 0x1F50){
                                 return (c >= 0x1F48 && c <= 0x1F4D);
                              } else {
                                 return (c >= 0x1F50 && c <= 0x1F57);
                              }
                           } else {
                              return (c >= 0x1F59 && c <= 0x1F59);
                           }
                        } else {
                           if(c < 0x1F5D){
                              return (c >= 0x1F5B && c <= 0x1F5B);
                           } else {
                              return (c >= 0x1F5D && c <= 0x1F5D);
                           }
                        }
                     } else {
                        if(c < 0x1FBE){
                           if(c < 0x1FB6){
                              if(c < 0x1F80){
                                 return (c >= 0x1F5F && c <= 0x1F7D);
                              } else {
                                 return (c >= 0x1F80 && c <= 0x1FB4);
                              }
                           } else {
                              return (c >= 0x1FB6 && c <= 0x1FBC);
                           }
                        } else {
                           if(c < 0x1FC2){
                              return (c >= 0x1FBE && c <= 0x1FBE);
                           } else {
                              return (c >= 0x1FC2 && c <= 0x1FC4);
                           }
                        }
                     }
                  } else {
                     if(c < 0x1FF6){
                        if(c < 0x1FE0){
                           if(c < 0x1FD6){
                              if(c < 0x1FD0){
                                 return (c >= 0x1FC6 && c <= 0x1FCC);
                              } else {
                                 return (c >= 0x1FD0 && c <= 0x1FD3);
                              }
                           } else {
                              return (c >= 0x1FD6 && c <= 0x1FDB);
                           }
                        } else {
                           if(c < 0x1FF2){
                              return (c >= 0x1FE0 && c <= 0x1FEC);
                           } else {
                              return (c >= 0x1FF2 && c <= 0x1FF4);
                           }
                        }
                     } else {
                        if(c < 0x2090){
                           if(c < 0x207F){
                              if(c < 0x2071){
                                 return (c >= 0x1FF6 && c <= 0x1FFC);
                              } else {
                                 return (c >= 0x2071 && c <= 0x2071);
                              }
                           } else {
                              return (c >= 0x207F && c <= 0x207F);
                           }
                        } else {
                           if(c < 0x2102){
                              return (c >= 0x2090 && c <= 0x209C);
                           } else {
                              return (c >= 0x2102 && c <= 0x2102);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x214E){
                     if(c < 0x2126){
                        if(c < 0x2118){
                           if(c < 0x2115){
                              if(c < 0x210A){
                                 return (c >= 0x2107 && c <= 0x2107);
                              } else {
                                 return (c >= 0x210A && c <= 0x2113);
                              }
                           } else {
                              return (c >= 0x2115 && c <= 0x2115);
                           }
                        } else {
                           if(c < 0x2124){
                              return (c >= 0x2118 && c <= 0x211D);
                           } else {
                              return (c >= 0x2124 && c <= 0x2124);
                           }
                        }
                     } else {
                        if(c < 0x213C){
                           if(c < 0x212A){
                              if(c < 0x2128){
                                 return (c >= 0x2126 && c <= 0x2126);
                              } else {
                                 return (c >= 0x2128 && c <= 0x2128);
                              }
                           } else {
                              return (c >= 0x212A && c <= 0x2139);
                           }
                        } else {
                           if(c < 0x2145){
                              return (c >= 0x213C && c <= 0x213F);
                           } else {
                              return (c >= 0x2145 && c <= 0x2149);
                           }
                        }
                     }
                  } else {
                     if(c < 0x2CEB){
                        if(c < 0x2C30){
                           if(c < 0x2C00){
                              if(c < 0x2160){
                                 return (c >= 0x214E && c <= 0x214E);
                              } else {
                                 return (c >= 0x2160 && c <= 0x2188);
                              }
                           } else {
                              return (c >= 0x2C00 && c <= 0x2C2E);
                           }
                        } else {
                           if(c < 0x2C60){
                              return (c >= 0x2C30 && c <= 0x2C5E);
                           } else {
                              return (c >= 0x2C60 && c <= 0x2CE4);
                           }
                        }
                     } else {
                        if(c < 0x2D00){
                           if(c < 0x2CF2){
                              return (c >= 0x2CEB && c <= 0x2CEE);
                           } else {
                              return (c >= 0x2CF2 && c <= 0x2CF3);
                           }
                        } else {
                           if(c < 0x2D27){
                              return (c >= 0x2D00 && c <= 0x2D25);
                           } else {
                              return (c >= 0x2D27 && c <= 0x2D27);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x30FC){
                  if(c < 0x2DD0){
                     if(c < 0x2DA8){
                        if(c < 0x2D80){
                           if(c < 0x2D6F){
                              if(c < 0x2D30){
                                 return (c >= 0x2D2D && c <= 0x2D2D);
                              } else {
                                 return (c >= 0x2D30 && c <= 0x2D67);
                              }
                           } else {
                              return (c >= 0x2D6F && c <= 0x2D6F);
                           }
                        } else {
                           if(c < 0x2DA0){
                              return (c >= 0x2D80 && c <= 0x2D96);
                           } else {
                              return (c >= 0x2DA0 && c <= 0x2DA6);
                           }
                        }
                     } else {
                        if(c < 0x2DC0){
                           if(c < 0x2DB8){
                              if(c < 0x2DB0){
                                 return (c >= 0x2DA8 && c <= 0x2DAE);
                              } else {
                                 return (c >= 0x2DB0 && c <= 0x2DB6);
                              }
                           } else {
                              return (c >= 0x2DB8 && c <= 0x2DBE);
                           }
                        } else {
                           if(c < 0x2DC8){
                              return (c >= 0x2DC0 && c <= 0x2DC6);
                           } else {
                              return (c >= 0x2DC8 && c <= 0x2DCE);
                           }
                        }
                     }
                  } else {
                     if(c < 0x3038){
                        if(c < 0x3021){
                           if(c < 0x3005){
                              if(c < 0x2DD8){
                                 return (c >= 0x2DD0 && c <= 0x2DD6);
                              } else {
                                 return (c >= 0x2DD8 && c <= 0x2DDE);
                              }
                           } else {
                              return (c >= 0x3005 && c <= 0x3007);
                           }
                        } else {
                           if(c < 0x3031){
                              return (c >= 0x3021 && c <= 0x3029);
                           } else {
                              return (c >= 0x3031 && c <= 0x3035);
                           }
                        }
                     } else {
                        if(c < 0x309B){
                           if(c < 0x3041){
                              return (c >= 0x3038 && c <= 0x303C);
                           } else {
                              return (c >= 0x3041 && c <= 0x3096);
                           }
                        } else {
                           if(c < 0x30A1){
                              return (c >= 0x309B && c <= 0x309F);
                           } else {
                              return (c >= 0x30A1 && c <= 0x30FA);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0xA610){
                     if(c < 0x3400){
                        if(c < 0x31A0){
                           if(c < 0x3131){
                              if(c < 0x3105){
                                 return (c >= 0x30FC && c <= 0x30FF);
                              } else {
                                 return (c >= 0x3105 && c <= 0x312F);
                              }
                           } else {
                              return (c >= 0x3131 && c <= 0x318E);
                           }
                        } else {
                           if(c < 0x31F0){
                              return (c >= 0x31A0 && c <= 0x31BF);
                           } else {
                              return (c >= 0x31F0 && c <= 0x31FF);
                           }
                        }
                     } else {
                        if(c < 0xA4D0){
                           if(c < 0xA000){
                              if(c < 0x4E00){
                                 return (c >= 0x3400 && c <= 0x4DBF);
                              } else {
                                 return (c >= 0x4E00 && c <= 0x9FFC);
                              }
                           } else {
                              return (c >= 0xA000 && c <= 0xA48C);
                           }
                        } else {
                           if(c < 0xA500){
                              return (c >= 0xA4D0 && c <= 0xA4FD);
                           } else {
                              return (c >= 0xA500 && c <= 0xA60C);
                           }
                        }
                     }
                  } else {
                     if(c < 0xA717){
                        if(c < 0xA67F){
                           if(c < 0xA640){
                              if(c < 0xA62A){
                                 return (c >= 0xA610 && c <= 0xA61F);
                              } else {
                                 return (c >= 0xA62A && c <= 0xA62B);
                              }
                           } else {
                              return (c >= 0xA640 && c <= 0xA66E);
                           }
                        } else {
                           if(c < 0xA6A0){
                              return (c >= 0xA67F && c <= 0xA69D);
                           } else {
                              return (c >= 0xA6A0 && c <= 0xA6EF);
                           }
                        }
                     } else {
                        if(c < 0xA78B){
                           if(c < 0xA722){
                              return (c >= 0xA717 && c <= 0xA71F);
                           } else {
                              return (c >= 0xA722 && c <= 0xA788);
                           }
                        } else {
                           if(c < 0xA7C2){
                              return (c >= 0xA78B && c <= 0xA7BF);
                           } else {
                              return (c >= 0xA7C2 && c <= 0xA7CA);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   } else {
      if(c < 0x011350){
         if(c < 0x01032D){
            if(c < 0xAC00){
               if(c < 0xAA60){
                  if(c < 0xA930){
                     if(c < 0xA882){
                        if(c < 0xA80C){
                           if(c < 0xA807){
                              if(c < 0xA803){
                                 return (c >= 0xA7F5 && c <= 0xA801);
                              } else {
                                 return (c >= 0xA803 && c <= 0xA805);
                              }
                           } else {
                              return (c >= 0xA807 && c <= 0xA80A);
                           }
                        } else {
                           if(c < 0xA840){
                              return (c >= 0xA80C && c <= 0xA822);
                           } else {
                              return (c >= 0xA840 && c <= 0xA873);
                           }
                        }
                     } else {
                        if(c < 0xA8FD){
                           if(c < 0xA8FB){
                              if(c < 0xA8F2){
                                 return (c >= 0xA882 && c <= 0xA8B3);
                              } else {
                                 return (c >= 0xA8F2 && c <= 0xA8F7);
                              }
                           } else {
                              return (c >= 0xA8FB && c <= 0xA8FB);
                           }
                        } else {
                           if(c < 0xA90A){
                              return (c >= 0xA8FD && c <= 0xA8FE);
                           } else {
                              return (c >= 0xA90A && c <= 0xA925);
                           }
                        }
                     }
                  } else {
                     if(c < 0xA9E6){
                        if(c < 0xA9CF){
                           if(c < 0xA984){
                              if(c < 0xA960){
                                 return (c >= 0xA930 && c <= 0xA946);
                              } else {
                                 return (c >= 0xA960 && c <= 0xA97C);
                              }
                           } else {
                              return (c >= 0xA984 && c <= 0xA9B2);
                           }
                        } else {
                           if(c < 0xA9E0){
                              return (c >= 0xA9CF && c <= 0xA9CF);
                           } else {
                              return (c >= 0xA9E0 && c <= 0xA9E4);
                           }
                        }
                     } else {
                        if(c < 0xAA40){
                           if(c < 0xAA00){
                              if(c < 0xA9FA){
                                 return (c >= 0xA9E6 && c <= 0xA9EF);
                              } else {
                                 return (c >= 0xA9FA && c <= 0xA9FE);
                              }
                           } else {
                              return (c >= 0xAA00 && c <= 0xAA28);
                           }
                        } else {
                           if(c < 0xAA44){
                              return (c >= 0xAA40 && c <= 0xAA42);
                           } else {
                              return (c >= 0xAA44 && c <= 0xAA4B);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0xAAF2){
                     if(c < 0xAAB9){
                        if(c < 0xAAB1){
                           if(c < 0xAA7E){
                              if(c < 0xAA7A){
                                 return (c >= 0xAA60 && c <= 0xAA76);
                              } else {
                                 return (c >= 0xAA7A && c <= 0xAA7A);
                              }
                           } else {
                              return (c >= 0xAA7E && c <= 0xAAAF);
                           }
                        } else {
                           if(c < 0xAAB5){
                              return (c >= 0xAAB1 && c <= 0xAAB1);
                           } else {
                              return (c >= 0xAAB5 && c <= 0xAAB6);
                           }
                        }
                     } else {
                        if(c < 0xAADB){
                           if(c < 0xAAC2){
                              if(c < 0xAAC0){
                                 return (c >= 0xAAB9 && c <= 0xAABD);
                              } else {
                                 return (c >= 0xAAC0 && c <= 0xAAC0);
                              }
                           } else {
                              return (c >= 0xAAC2 && c <= 0xAAC2);
                           }
                        } else {
                           if(c < 0xAAE0){
                              return (c >= 0xAADB && c <= 0xAADD);
                           } else {
                              return (c >= 0xAAE0 && c <= 0xAAEA);
                           }
                        }
                     }
                  } else {
                     if(c < 0xAB28){
                        if(c < 0xAB11){
                           if(c < 0xAB09){
                              if(c < 0xAB01){
                                 return (c >= 0xAAF2 && c <= 0xAAF4);
                              } else {
                                 return (c >= 0xAB01 && c <= 0xAB06);
                              }
                           } else {
                              return (c >= 0xAB09 && c <= 0xAB0E);
                           }
                        } else {
                           if(c < 0xAB20){
                              return (c >= 0xAB11 && c <= 0xAB16);
                           } else {
                              return (c >= 0xAB20 && c <= 0xAB26);
                           }
                        }
                     } else {
                        if(c < 0xAB5C){
                           if(c < 0xAB30){
                              return (c >= 0xAB28 && c <= 0xAB2E);
                           } else {
                              return (c >= 0xAB30 && c <= 0xAB5A);
                           }
                        } else {
                           if(c < 0xAB70){
                              return (c >= 0xAB5C && c <= 0xAB69);
                           } else {
                              return (c >= 0xAB70 && c <= 0xABE2);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0xFE76){
                  if(c < 0xFB38){
                     if(c < 0xFB00){
                        if(c < 0xF900){
                           if(c < 0xD7CB){
                              if(c < 0xD7B0){
                                 return (c >= 0xAC00 && c <= 0xD7A3);
                              } else {
                                 return (c >= 0xD7B0 && c <= 0xD7C6);
                              }
                           } else {
                              return (c >= 0xD7CB && c <= 0xD7FB);
                           }
                        } else {
                           if(c < 0xFA70){
                              return (c >= 0xF900 && c <= 0xFA6D);
                           } else {
                              return (c >= 0xFA70 && c <= 0xFAD9);
                           }
                        }
                     } else {
                        if(c < 0xFB1F){
                           if(c < 0xFB1D){
                              if(c < 0xFB13){
                                 return (c >= 0xFB00 && c <= 0xFB06);
                              } else {
                                 return (c >= 0xFB13 && c <= 0xFB17);
                              }
                           } else {
                              return (c >= 0xFB1D && c <= 0xFB1D);
                           }
                        } else {
                           if(c < 0xFB2A){
                              return (c >= 0xFB1F && c <= 0xFB28);
                           } else {
                              return (c >= 0xFB2A && c <= 0xFB36);
                           }
                        }
                     }
                  } else {
                     if(c < 0xFBD3){
                        if(c < 0xFB43){
                           if(c < 0xFB40){
                              if(c < 0xFB3E){
                                 return (c >= 0xFB38 && c <= 0xFB3C);
                              } else {
                                 return (c >= 0xFB3E && c <= 0xFB3E);
                              }
                           } else {
                              return (c >= 0xFB40 && c <= 0xFB41);
                           }
                        } else {
                           if(c < 0xFB46){
                              return (c >= 0xFB43 && c <= 0xFB44);
                           } else {
                              return (c >= 0xFB46 && c <= 0xFBB1);
                           }
                        }
                     } else {
                        if(c < 0xFDF0){
                           if(c < 0xFD92){
                              if(c < 0xFD50){
                                 return (c >= 0xFBD3 && c <= 0xFD3D);
                              } else {
                                 return (c >= 0xFD50 && c <= 0xFD8F);
                              }
                           } else {
                              return (c >= 0xFD92 && c <= 0xFDC7);
                           }
                        } else {
                           if(c < 0xFE70){
                              return (c >= 0xFDF0 && c <= 0xFDFB);
                           } else {
                              return (c >= 0xFE70 && c <= 0xFE74);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x010028){
                     if(c < 0xFFCA){
                        if(c < 0xFF66){
                           if(c < 0xFF41){
                              if(c < 0xFF21){
                                 return (c >= 0xFE76 && c <= 0xFEFC);
                              } else {
                                 return (c >= 0xFF21 && c <= 0xFF3A);
                              }
                           } else {
                              return (c >= 0xFF41 && c <= 0xFF5A);
                           }
                        } else {
                           if(c < 0xFFC2){
                              return (c >= 0xFF66 && c <= 0xFFBE);
                           } else {
                              return (c >= 0xFFC2 && c <= 0xFFC7);
                           }
                        }
                     } else {
                        if(c < 0x010000){
                           if(c < 0xFFDA){
                              if(c < 0xFFD2){
                                 return (c >= 0xFFCA && c <= 0xFFCF);
                              } else {
                                 return (c >= 0xFFD2 && c <= 0xFFD7);
                              }
                           } else {
                              return (c >= 0xFFDA && c <= 0xFFDC);
                           }
                        } else {
                           if(c < 0x01000D){
                              return (c >= 0x010000 && c <= 0x01000B);
                           } else {
                              return (c >= 0x01000D && c <= 0x010026);
                           }
                        }
                     }
                  } else {
                     if(c < 0x010140){
                        if(c < 0x010050){
                           if(c < 0x01003F){
                              if(c < 0x01003C){
                                 return (c >= 0x010028 && c <= 0x01003A);
                              } else {
                                 return (c >= 0x01003C && c <= 0x01003D);
                              }
                           } else {
                              return (c >= 0x01003F && c <= 0x01004D);
                           }
                        } else {
                           if(c < 0x010080){
                              return (c >= 0x010050 && c <= 0x01005D);
                           } else {
                              return (c >= 0x010080 && c <= 0x0100FA);
                           }
                        }
                     } else {
                        if(c < 0x0102A0){
                           if(c < 0x010280){
                              return (c >= 0x010140 && c <= 0x010174);
                           } else {
                              return (c >= 0x010280 && c <= 0x01029C);
                           }
                        } else {
                           if(c < 0x010300){
                              return (c >= 0x0102A0 && c <= 0x0102D0);
                           } else {
                              return (c >= 0x010300 && c <= 0x01031F);
                           }
                        }
                     }
                  }
               }
            }
         } else {
            if(c < 0x010B80){
               if(c < 0x010860){
                  if(c < 0x010530){
                     if(c < 0x0103D1){
                        if(c < 0x0103A0){
                           if(c < 0x010380){
                              if(c < 0x010350){
                                 return (c >= 0x01032D && c <= 0x01034A);
                              } else {
                                 return (c >= 0x010350 && c <= 0x010375);
                              }
                           } else {
                              return (c >= 0x010380 && c <= 0x01039D);
                           }
                        } else {
                           if(c < 0x0103C8){
                              return (c >= 0x0103A0 && c <= 0x0103C3);
                           } else {
                              return (c >= 0x0103C8 && c <= 0x0103CF);
                           }
                        }
                     } else {
                        if(c < 0x0104D8){
                           if(c < 0x0104B0){
                              if(c < 0x010400){
                                 return (c >= 0x0103D1 && c <= 0x0103D5);
                              } else {
                                 return (c >= 0x010400 && c <= 0x01049D);
                              }
                           } else {
                              return (c >= 0x0104B0 && c <= 0x0104D3);
                           }
                        } else {
                           if(c < 0x010500){
                              return (c >= 0x0104D8 && c <= 0x0104FB);
                           } else {
                              return (c >= 0x010500 && c <= 0x010527);
                           }
                        }
                     }
                  } else {
                     if(c < 0x010808){
                        if(c < 0x010760){
                           if(c < 0x010740){
                              if(c < 0x010600){
                                 return (c >= 0x010530 && c <= 0x010563);
                              } else {
                                 return (c >= 0x010600 && c <= 0x010736);
                              }
                           } else {
                              return (c >= 0x010740 && c <= 0x010755);
                           }
                        } else {
                           if(c < 0x010800){
                              return (c >= 0x010760 && c <= 0x010767);
                           } else {
                              return (c >= 0x010800 && c <= 0x010805);
                           }
                        }
                     } else {
                        if(c < 0x01083C){
                           if(c < 0x010837){
                              if(c < 0x01080A){
                                 return (c >= 0x010808 && c <= 0x010808);
                              } else {
                                 return (c >= 0x01080A && c <= 0x010835);
                              }
                           } else {
                              return (c >= 0x010837 && c <= 0x010838);
                           }
                        } else {
                           if(c < 0x01083F){
                              return (c >= 0x01083C && c <= 0x01083C);
                           } else {
                              return (c >= 0x01083F && c <= 0x010855);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x010A15){
                     if(c < 0x010920){
                        if(c < 0x0108F4){
                           if(c < 0x0108E0){
                              if(c < 0x010880){
                                 return (c >= 0x010860 && c <= 0x010876);
                              } else {
                                 return (c >= 0x010880 && c <= 0x01089E);
                              }
                           } else {
                              return (c >= 0x0108E0 && c <= 0x0108F2);
                           }
                        } else {
                           if(c < 0x010900){
                              return (c >= 0x0108F4 && c <= 0x0108F5);
                           } else {
                              return (c >= 0x010900 && c <= 0x010915);
                           }
                        }
                     } else {
                        if(c < 0x010A00){
                           if(c < 0x0109BE){
                              if(c < 0x010980){
                                 return (c >= 0x010920 && c <= 0x010939);
                              } else {
                                 return (c >= 0x010980 && c <= 0x0109B7);
                              }
                           } else {
                              return (c >= 0x0109BE && c <= 0x0109BF);
                           }
                        } else {
                           if(c < 0x010A10){
                              return (c >= 0x010A00 && c <= 0x010A00);
                           } else {
                              return (c >= 0x010A10 && c <= 0x010A13);
                           }
                        }
                     }
                  } else {
                     if(c < 0x010AC9){
                        if(c < 0x010A80){
                           if(c < 0x010A60){
                              if(c < 0x010A19){
                                 return (c >= 0x010A15 && c <= 0x010A17);
                              } else {
                                 return (c >= 0x010A19 && c <= 0x010A35);
                              }
                           } else {
                              return (c >= 0x010A60 && c <= 0x010A7C);
                           }
                        } else {
                           if(c < 0x010AC0){
                              return (c >= 0x010A80 && c <= 0x010A9C);
                           } else {
                              return (c >= 0x010AC0 && c <= 0x010AC7);
                           }
                        }
                     } else {
                        if(c < 0x010B40){
                           if(c < 0x010B00){
                              return (c >= 0x010AC9 && c <= 0x010AE4);
                           } else {
                              return (c >= 0x010B00 && c <= 0x010B35);
                           }
                        } else {
                           if(c < 0x010B60){
                              return (c >= 0x010B40 && c <= 0x010B55);
                           } else {
                              return (c >= 0x010B60 && c <= 0x010B72);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x011183){
                  if(c < 0x010FB0){
                     if(c < 0x010E80){
                        if(c < 0x010CC0){
                           if(c < 0x010C80){
                              if(c < 0x010C00){
                                 return (c >= 0x010B80 && c <= 0x010B91);
                              } else {
                                 return (c >= 0x010C00 && c <= 0x010C48);
                              }
                           } else {
                              return (c >= 0x010C80 && c <= 0x010CB2);
                           }
                        } else {
                           if(c < 0x010D00){
                              return (c >= 0x010CC0 && c <= 0x010CF2);
                           } else {
                              return (c >= 0x010D00 && c <= 0x010D23);
                           }
                        }
                     } else {
                        if(c < 0x010F27){
                           if(c < 0x010F00){
                              if(c < 0x010EB0){
                                 return (c >= 0x010E80 && c <= 0x010EA9);
                              } else {
                                 return (c >= 0x010EB0 && c <= 0x010EB1);
                              }
                           } else {
                              return (c >= 0x010F00 && c <= 0x010F1C);
                           }
                        } else {
                           if(c < 0x010F30){
                              return (c >= 0x010F27 && c <= 0x010F27);
                           } else {
                              return (c >= 0x010F30 && c <= 0x010F45);
                           }
                        }
                     }
                  } else {
                     if(c < 0x011103){
                        if(c < 0x011083){
                           if(c < 0x011003){
                              if(c < 0x010FE0){
                                 return (c >= 0x010FB0 && c <= 0x010FC4);
                              } else {
                                 return (c >= 0x010FE0 && c <= 0x010FF6);
                              }
                           } else {
                              return (c >= 0x011003 && c <= 0x011037);
                           }
                        } else {
                           if(c < 0x0110D0){
                              return (c >= 0x011083 && c <= 0x0110AF);
                           } else {
                              return (c >= 0x0110D0 && c <= 0x0110E8);
                           }
                        }
                     } else {
                        if(c < 0x011150){
                           if(c < 0x011147){
                              if(c < 0x011144){
                                 return (c >= 0x011103 && c <= 0x011126);
                              } else {
                                 return (c >= 0x011144 && c <= 0x011144);
                              }
                           } else {
                              return (c >= 0x011147 && c <= 0x011147);
                           }
                        } else {
                           if(c < 0x011176){
                              return (c >= 0x011150 && c <= 0x011172);
                           } else {
                              return (c >= 0x011176 && c <= 0x011176);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x01129F){
                     if(c < 0x011213){
                        if(c < 0x0111DC){
                           if(c < 0x0111DA){
                              if(c < 0x0111C1){
                                 return (c >= 0x011183 && c <= 0x0111B2);
                              } else {
                                 return (c >= 0x0111C1 && c <= 0x0111C4);
                              }
                           } else {
                              return (c >= 0x0111DA && c <= 0x0111DA);
                           }
                        } else {
                           if(c < 0x011200){
                              return (c >= 0x0111DC && c <= 0x0111DC);
                           } else {
                              return (c >= 0x011200 && c <= 0x011211);
                           }
                        }
                     } else {
                        if(c < 0x01128A){
                           if(c < 0x011288){
                              if(c < 0x011280){
                                 return (c >= 0x011213 && c <= 0x01122B);
                              } else {
                                 return (c >= 0x011280 && c <= 0x011286);
                              }
                           } else {
                              return (c >= 0x011288 && c <= 0x011288);
                           }
                        } else {
                           if(c < 0x01128F){
                              return (c >= 0x01128A && c <= 0x01128D);
                           } else {
                              return (c >= 0x01128F && c <= 0x01129D);
                           }
                        }
                     }
                  } else {
                     if(c < 0x01132A){
                        if(c < 0x01130F){
                           if(c < 0x011305){
                              if(c < 0x0112B0){
                                 return (c >= 0x01129F && c <= 0x0112A8);
                              } else {
                                 return (c >= 0x0112B0 && c <= 0x0112DE);
                              }
                           } else {
                              return (c >= 0x011305 && c <= 0x01130C);
                           }
                        } else {
                           if(c < 0x011313){
                              return (c >= 0x01130F && c <= 0x011310);
                           } else {
                              return (c >= 0x011313 && c <= 0x011328);
                           }
                        }
                     } else {
                        if(c < 0x011335){
                           if(c < 0x011332){
                              return (c >= 0x01132A && c <= 0x011330);
                           } else {
                              return (c >= 0x011332 && c <= 0x011333);
                           }
                        } else {
                           if(c < 0x01133D){
                              return (c >= 0x011335 && c <= 0x011339);
                           } else {
                              return (c >= 0x01133D && c <= 0x01133D);
                           }
                        }
                     }
                  }
               }
            }
         }
      } else {
         if(c < 0x01D400){
            if(c < 0x011D00){
               if(c < 0x011915){
                  if(c < 0x011600){
                     if(c < 0x011480){
                        if(c < 0x011447){
                           if(c < 0x011400){
                              if(c < 0x01135D){
                                 return (c >= 0x011350 && c <= 0x011350);
                              } else {
                                 return (c >= 0x01135D && c <= 0x011361);
                              }
                           } else {
                              return (c >= 0x011400 && c <= 0x011434);
                           }
                        } else {
                           if(c < 0x01145F){
                              return (c >= 0x011447 && c <= 0x01144A);
                           } else {
                              return (c >= 0x01145F && c <= 0x011461);
                           }
                        }
                     } else {
                        if(c < 0x011580){
                           if(c < 0x0114C7){
                              if(c < 0x0114C4){
                                 return (c >= 0x011480 && c <= 0x0114AF);
                              } else {
                                 return (c >= 0x0114C4 && c <= 0x0114C5);
                              }
                           } else {
                              return (c >= 0x0114C7 && c <= 0x0114C7);
                           }
                        } else {
                           if(c < 0x0115D8){
                              return (c >= 0x011580 && c <= 0x0115AE);
                           } else {
                              return (c >= 0x0115D8 && c <= 0x0115DB);
                           }
                        }
                     }
                  } else {
                     if(c < 0x011800){
                        if(c < 0x0116B8){
                           if(c < 0x011680){
                              if(c < 0x011644){
                                 return (c >= 0x011600 && c <= 0x01162F);
                              } else {
                                 return (c >= 0x011644 && c <= 0x011644);
                              }
                           } else {
                              return (c >= 0x011680 && c <= 0x0116AA);
                           }
                        } else {
                           if(c < 0x011700){
                              return (c >= 0x0116B8 && c <= 0x0116B8);
                           } else {
                              return (c >= 0x011700 && c <= 0x01171A);
                           }
                        }
                     } else {
                        if(c < 0x011909){
                           if(c < 0x0118FF){
                              if(c < 0x0118A0){
                                 return (c >= 0x011800 && c <= 0x01182B);
                              } else {
                                 return (c >= 0x0118A0 && c <= 0x0118DF);
                              }
                           } else {
                              return (c >= 0x0118FF && c <= 0x011906);
                           }
                        } else {
                           if(c < 0x01190C){
                              return (c >= 0x011909 && c <= 0x011909);
                           } else {
                              return (c >= 0x01190C && c <= 0x011913);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x011A3A){
                     if(c < 0x0119AA){
                        if(c < 0x011941){
                           if(c < 0x01193F){
                              if(c < 0x011918){
                                 return (c >= 0x011915 && c <= 0x011916);
                              } else {
                                 return (c >= 0x011918 && c <= 0x01192F);
                              }
                           } else {
                              return (c >= 0x01193F && c <= 0x01193F);
                           }
                        } else {
                           if(c < 0x0119A0){
                              return (c >= 0x011941 && c <= 0x011941);
                           } else {
                              return (c >= 0x0119A0 && c <= 0x0119A7);
                           }
                        }
                     } else {
                        if(c < 0x011A00){
                           if(c < 0x0119E3){
                              if(c < 0x0119E1){
                                 return (c >= 0x0119AA && c <= 0x0119D0);
                              } else {
                                 return (c >= 0x0119E1 && c <= 0x0119E1);
                              }
                           } else {
                              return (c >= 0x0119E3 && c <= 0x0119E3);
                           }
                        } else {
                           if(c < 0x011A0B){
                              return (c >= 0x011A00 && c <= 0x011A00);
                           } else {
                              return (c >= 0x011A0B && c <= 0x011A32);
                           }
                        }
                     }
                  } else {
                     if(c < 0x011C00){
                        if(c < 0x011A9D){
                           if(c < 0x011A5C){
                              if(c < 0x011A50){
                                 return (c >= 0x011A3A && c <= 0x011A3A);
                              } else {
                                 return (c >= 0x011A50 && c <= 0x011A50);
                              }
                           } else {
                              return (c >= 0x011A5C && c <= 0x011A89);
                           }
                        } else {
                           if(c < 0x011AC0){
                              return (c >= 0x011A9D && c <= 0x011A9D);
                           } else {
                              return (c >= 0x011AC0 && c <= 0x011AF8);
                           }
                        }
                     } else {
                        if(c < 0x011C40){
                           if(c < 0x011C0A){
                              return (c >= 0x011C00 && c <= 0x011C08);
                           } else {
                              return (c >= 0x011C0A && c <= 0x011C2E);
                           }
                        } else {
                           if(c < 0x011C72){
                              return (c >= 0x011C40 && c <= 0x011C40);
                           } else {
                              return (c >= 0x011C72 && c <= 0x011C8F);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x016B63){
                  if(c < 0x012000){
                     if(c < 0x011D67){
                        if(c < 0x011D46){
                           if(c < 0x011D0B){
                              if(c < 0x011D08){
                                 return (c >= 0x011D00 && c <= 0x011D06);
                              } else {
                                 return (c >= 0x011D08 && c <= 0x011D09);
                              }
                           } else {
                              return (c >= 0x011D0B && c <= 0x011D30);
                           }
                        } else {
                           if(c < 0x011D60){
                              return (c >= 0x011D46 && c <= 0x011D46);
                           } else {
                              return (c >= 0x011D60 && c <= 0x011D65);
                           }
                        }
                     } else {
                        if(c < 0x011EE0){
                           if(c < 0x011D98){
                              if(c < 0x011D6A){
                                 return (c >= 0x011D67 && c <= 0x011D68);
                              } else {
                                 return (c >= 0x011D6A && c <= 0x011D89);
                              }
                           } else {
                              return (c >= 0x011D98 && c <= 0x011D98);
                           }
                        } else {
                           if(c < 0x011FB0){
                              return (c >= 0x011EE0 && c <= 0x011EF2);
                           } else {
                              return (c >= 0x011FB0 && c <= 0x011FB0);
                           }
                        }
                     }
                  } else {
                     if(c < 0x016800){
                        if(c < 0x013000){
                           if(c < 0x012480){
                              if(c < 0x012400){
                                 return (c >= 0x012000 && c <= 0x012399);
                              } else {
                                 return (c >= 0x012400 && c <= 0x01246E);
                              }
                           } else {
                              return (c >= 0x012480 && c <= 0x012543);
                           }
                        } else {
                           if(c < 0x014400){
                              return (c >= 0x013000 && c <= 0x01342E);
                           } else {
                              return (c >= 0x014400 && c <= 0x014646);
                           }
                        }
                     } else {
                        if(c < 0x016B00){
                           if(c < 0x016AD0){
                              if(c < 0x016A40){
                                 return (c >= 0x016800 && c <= 0x016A38);
                              } else {
                                 return (c >= 0x016A40 && c <= 0x016A5E);
                              }
                           } else {
                              return (c >= 0x016AD0 && c <= 0x016AED);
                           }
                        } else {
                           if(c < 0x016B40){
                              return (c >= 0x016B00 && c <= 0x016B2F);
                           } else {
                              return (c >= 0x016B40 && c <= 0x016B43);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x018D00){
                     if(c < 0x016F93){
                        if(c < 0x016F00){
                           if(c < 0x016E40){
                              if(c < 0x016B7D){
                                 return (c >= 0x016B63 && c <= 0x016B77);
                              } else {
                                 return (c >= 0x016B7D && c <= 0x016B8F);
                              }
                           } else {
                              return (c >= 0x016E40 && c <= 0x016E7F);
                           }
                        } else {
                           if(c < 0x016F50){
                              return (c >= 0x016F00 && c <= 0x016F4A);
                           } else {
                              return (c >= 0x016F50 && c <= 0x016F50);
                           }
                        }
                     } else {
                        if(c < 0x017000){
                           if(c < 0x016FE3){
                              if(c < 0x016FE0){
                                 return (c >= 0x016F93 && c <= 0x016F9F);
                              } else {
                                 return (c >= 0x016FE0 && c <= 0x016FE1);
                              }
                           } else {
                              return (c >= 0x016FE3 && c <= 0x016FE3);
                           }
                        } else {
                           if(c < 0x018800){
                              return (c >= 0x017000 && c <= 0x0187F7);
                           } else {
                              return (c >= 0x018800 && c <= 0x018CD5);
                           }
                        }
                     }
                  } else {
                     if(c < 0x01BC00){
                        if(c < 0x01B164){
                           if(c < 0x01B150){
                              if(c < 0x01B000){
                                 return (c >= 0x018D00 && c <= 0x018D08);
                              } else {
                                 return (c >= 0x01B000 && c <= 0x01B11E);
                              }
                           } else {
                              return (c >= 0x01B150 && c <= 0x01B152);
                           }
                        } else {
                           if(c < 0x01B170){
                              return (c >= 0x01B164 && c <= 0x01B167);
                           } else {
                              return (c >= 0x01B170 && c <= 0x01B2FB);
                           }
                        }
                     } else {
                        if(c < 0x01BC80){
                           if(c < 0x01BC70){
                              return (c >= 0x01BC00 && c <= 0x01BC6A);
                           } else {
                              return (c >= 0x01BC70 && c <= 0x01BC7C);
                           }
                        } else {
                           if(c < 0x01BC90){
                              return (c >= 0x01BC80 && c <= 0x01BC88);
                           } else {
                              return (c >= 0x01BC90 && c <= 0x01BC99);
                           }
                        }
                     }
                  }
               }
            }
         } else {
            if(c < 0x01EE21){
               if(c < 0x01D6C2){
                  if(c < 0x01D507){
                     if(c < 0x01D4A9){
                        if(c < 0x01D4A2){
                           if(c < 0x01D49E){
                              if(c < 0x01D456){
                                 return (c >= 0x01D400 && c <= 0x01D454);
                              } else {
                                 return (c >= 0x01D456 && c <= 0x01D49C);
                              }
                           } else {
                              return (c >= 0x01D49E && c <= 0x01D49F);
                           }
                        } else {
                           if(c < 0x01D4A5){
                              return (c >= 0x01D4A2 && c <= 0x01D4A2);
                           } else {
                              return (c >= 0x01D4A5 && c <= 0x01D4A6);
                           }
                        }
                     } else {
                        if(c < 0x01D4BD){
                           if(c < 0x01D4BB){
                              if(c < 0x01D4AE){
                                 return (c >= 0x01D4A9 && c <= 0x01D4AC);
                              } else {
                                 return (c >= 0x01D4AE && c <= 0x01D4B9);
                              }
                           } else {
                              return (c >= 0x01D4BB && c <= 0x01D4BB);
                           }
                        } else {
                           if(c < 0x01D4C5){
                              return (c >= 0x01D4BD && c <= 0x01D4C3);
                           } else {
                              return (c >= 0x01D4C5 && c <= 0x01D505);
                           }
                        }
                     }
                  } else {
                     if(c < 0x01D540){
                        if(c < 0x01D51E){
                           if(c < 0x01D516){
                              if(c < 0x01D50D){
                                 return (c >= 0x01D507 && c <= 0x01D50A);
                              } else {
                                 return (c >= 0x01D50D && c <= 0x01D514);
                              }
                           } else {
                              return (c >= 0x01D516 && c <= 0x01D51C);
                           }
                        } else {
                           if(c < 0x01D53B){
                              return (c >= 0x01D51E && c <= 0x01D539);
                           } else {
                              return (c >= 0x01D53B && c <= 0x01D53E);
                           }
                        }
                     } else {
                        if(c < 0x01D552){
                           if(c < 0x01D54A){
                              if(c < 0x01D546){
                                 return (c >= 0x01D540 && c <= 0x01D544);
                              } else {
                                 return (c >= 0x01D546 && c <= 0x01D546);
                              }
                           } else {
                              return (c >= 0x01D54A && c <= 0x01D550);
                           }
                        } else {
                           if(c < 0x01D6A8){
                              return (c >= 0x01D552 && c <= 0x01D6A5);
                           } else {
                              return (c >= 0x01D6A8 && c <= 0x01D6C0);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x01E100){
                     if(c < 0x01D750){
                        if(c < 0x01D716){
                           if(c < 0x01D6FC){
                              if(c < 0x01D6DC){
                                 return (c >= 0x01D6C2 && c <= 0x01D6DA);
                              } else {
                                 return (c >= 0x01D6DC && c <= 0x01D6FA);
                              }
                           } else {
                              return (c >= 0x01D6FC && c <= 0x01D714);
                           }
                        } else {
                           if(c < 0x01D736){
                              return (c >= 0x01D716 && c <= 0x01D734);
                           } else {
                              return (c >= 0x01D736 && c <= 0x01D74E);
                           }
                        }
                     } else {
                        if(c < 0x01D7AA){
                           if(c < 0x01D78A){
                              if(c < 0x01D770){
                                 return (c >= 0x01D750 && c <= 0x01D76E);
                              } else {
                                 return (c >= 0x01D770 && c <= 0x01D788);
                              }
                           } else {
                              return (c >= 0x01D78A && c <= 0x01D7A8);
                           }
                        } else {
                           if(c < 0x01D7C4){
                              return (c >= 0x01D7AA && c <= 0x01D7C2);
                           } else {
                              return (c >= 0x01D7C4 && c <= 0x01D7CB);
                           }
                        }
                     }
                  } else {
                     if(c < 0x01E900){
                        if(c < 0x01E2C0){
                           if(c < 0x01E14E){
                              if(c < 0x01E137){
                                 return (c >= 0x01E100 && c <= 0x01E12C);
                              } else {
                                 return (c >= 0x01E137 && c <= 0x01E13D);
                              }
                           } else {
                              return (c >= 0x01E14E && c <= 0x01E14E);
                           }
                        } else {
                           if(c < 0x01E800){
                              return (c >= 0x01E2C0 && c <= 0x01E2EB);
                           } else {
                              return (c >= 0x01E800 && c <= 0x01E8C4);
                           }
                        }
                     } else {
                        if(c < 0x01EE00){
                           if(c < 0x01E94B){
                              return (c >= 0x01E900 && c <= 0x01E943);
                           } else {
                              return (c >= 0x01E94B && c <= 0x01E94B);
                           }
                        } else {
                           if(c < 0x01EE05){
                              return (c >= 0x01EE00 && c <= 0x01EE03);
                           } else {
                              return (c >= 0x01EE05 && c <= 0x01EE1F);
                           }
                        }
                     }
                  }
               }
            } else {
               if(c < 0x01EE61){
                  if(c < 0x01EE4B){
                     if(c < 0x01EE39){
                        if(c < 0x01EE29){
                           if(c < 0x01EE27){
                              if(c < 0x01EE24){
                                 return (c >= 0x01EE21 && c <= 0x01EE22);
                              } else {
                                 return (c >= 0x01EE24 && c <= 0x01EE24);
                              }
                           } else {
                              return (c >= 0x01EE27 && c <= 0x01EE27);
                           }
                        } else {
                           if(c < 0x01EE34){
                              return (c >= 0x01EE29 && c <= 0x01EE32);
                           } else {
                              return (c >= 0x01EE34 && c <= 0x01EE37);
                           }
                        }
                     } else {
                        if(c < 0x01EE47){
                           if(c < 0x01EE42){
                              if(c < 0x01EE3B){
                                 return (c >= 0x01EE39 && c <= 0x01EE39);
                              } else {
                                 return (c >= 0x01EE3B && c <= 0x01EE3B);
                              }
                           } else {
                              return (c >= 0x01EE42 && c <= 0x01EE42);
                           }
                        } else {
                           if(c < 0x01EE49){
                              return (c >= 0x01EE47 && c <= 0x01EE47);
                           } else {
                              return (c >= 0x01EE49 && c <= 0x01EE49);
                           }
                        }
                     }
                  } else {
                     if(c < 0x01EE59){
                        if(c < 0x01EE54){
                           if(c < 0x01EE51){
                              if(c < 0x01EE4D){
                                 return (c >= 0x01EE4B && c <= 0x01EE4B);
                              } else {
                                 return (c >= 0x01EE4D && c <= 0x01EE4F);
                              }
                           } else {
                              return (c >= 0x01EE51 && c <= 0x01EE52);
                           }
                        } else {
                           if(c < 0x01EE57){
                              return (c >= 0x01EE54 && c <= 0x01EE54);
                           } else {
                              return (c >= 0x01EE57 && c <= 0x01EE57);
                           }
                        }
                     } else {
                        if(c < 0x01EE5D){
                           if(c < 0x01EE5B){
                              return (c >= 0x01EE59 && c <= 0x01EE59);
                           } else {
                              return (c >= 0x01EE5B && c <= 0x01EE5B);
                           }
                        } else {
                           if(c < 0x01EE5F){
                              return (c >= 0x01EE5D && c <= 0x01EE5D);
                           } else {
                              return (c >= 0x01EE5F && c <= 0x01EE5F);
                           }
                        }
                     }
                  }
               } else {
                  if(c < 0x01EEA5){
                     if(c < 0x01EE79){
                        if(c < 0x01EE6C){
                           if(c < 0x01EE67){
                              if(c < 0x01EE64){
                                 return (c >= 0x01EE61 && c <= 0x01EE62);
                              } else {
                                 return (c >= 0x01EE64 && c <= 0x01EE64);
                              }
                           } else {
                              return (c >= 0x01EE67 && c <= 0x01EE6A);
                           }
                        } else {
                           if(c < 0x01EE74){
                              return (c >= 0x01EE6C && c <= 0x01EE72);
                           } else {
                              return (c >= 0x01EE74 && c <= 0x01EE77);
                           }
                        }
                     } else {
                        if(c < 0x01EE8B){
                           if(c < 0x01EE80){
                              if(c < 0x01EE7E){
                                 return (c >= 0x01EE79 && c <= 0x01EE7C);
                              } else {
                                 return (c >= 0x01EE7E && c <= 0x01EE7E);
                              }
                           } else {
                              return (c >= 0x01EE80 && c <= 0x01EE89);
                           }
                        } else {
                           if(c < 0x01EEA1){
                              return (c >= 0x01EE8B && c <= 0x01EE9B);
                           } else {
                              return (c >= 0x01EEA1 && c <= 0x01EEA3);
                           }
                        }
                     }
                  } else {
                     if(c < 0x02B820){
                        if(c < 0x02A700){
                           if(c < 0x020000){
                              if(c < 0x01EEAB){
                                 return (c >= 0x01EEA5 && c <= 0x01EEA9);
                              } else {
                                 return (c >= 0x01EEAB && c <= 0x01EEBB);
                              }
                           } else {
                              return (c >= 0x020000 && c <= 0x02A6DD);
                           }
                        } else {
                           if(c < 0x02B740){
                              return (c >= 0x02A700 && c <= 0x02B734);
                           } else {
                              return (c >= 0x02B740 && c <= 0x02B81D);
                           }
                        }
                     } else {
                        if(c < 0x02F800){
                           if(c < 0x02CEB0){
                              return (c >= 0x02B820 && c <= 0x02CEA1);
                           } else {
                              return (c >= 0x02CEB0 && c <= 0x02EBE0);
                           }
                        } else {
                           if(c < 0x030000){
                              return (c >= 0x02F800 && c <= 0x02FA1D);
                           } else {
                              return (c >= 0x030000 && c <= 0x03134A);
                           }
                        }
                     }
                  }
               }
            }
         }
      }
   }
}
